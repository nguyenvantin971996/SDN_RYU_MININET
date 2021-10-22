REFERENCE_BW = 10000000

DEFAULT_BW = 10000000

MAX_PATHS = 1
class AlgorithmDijkstra(object):
    def __init__(self, adjacency, bandwidths,switches):
        self.switches = switches
        self.adjacency = adjacency
        self.bandwidths = bandwidths
        self._distance = {}
        self._previous = {}
        self._viewed_switches = []

    def get_paths(self, src, dst):
        paths = []
        for switch in self.switches:
            self._distance[switch] = float("+inf")
            self._previous[switch] = None
        self._viewed_switches = set(self.switches)
        self._distance[src] = 0
        while len(self._viewed_switches) > 0:
            current_switch = self._find_nearest_switch()
            if not current_switch:
                break
            self._viewed_switches.remove(current_switch)
            for switch in set(self.adjacency[current_switch].keys()):
                tmp_distance = self._distance[current_switch] + self.get_link_cost(current_switch,switch)
                if tmp_distance < self._distance[switch]:
                    self._distance[switch] = tmp_distance
                    self._previous[switch] = current_switch
        path = self._recover_path(src,dst)
        paths.append(path)
        return paths

    def _recover_path(self,src,dst):
        path = [dst]
        current_switch = self._previous[dst]
        while current_switch is not None:
            path.append(current_switch)
            current_switch= self._previous[current_switch]
        path.reverse()
        return path

    def _find_nearest_switch(self):
        min_distance = float('+inf')
        nearest_switch = None
        for switch in self._viewed_switches:
            if self._distance[switch] < min_distance:
                min_distance = self._distance[switch]
                nearest_switch = switch
        return nearest_switch

    def get_link_cost(self, s1, s2):
        '''
        Get the link cost between two switches 
        '''
        e1 = self.adjacency[s1][s2]
        e2 = self.adjacency[s2][s1]
        bl = min(self.bandwidths[s1][e1], self.bandwidths[s2][e2])
        ew = int(REFERENCE_BW/bl)
        return ew
    def get_path_cost(self, path):
        '''
        Get the path cost
        '''
        cost = 0
        for i in range(len(path) - 1):
            cost += self.get_link_cost(path[i], path[i+1])
        return cost
    def get_optimal_paths(self, src, dst):
        '''
        Get the n-most optimal paths according to MAX_PATHS
        '''
        paths = self.get_paths(src, dst)
        paths_count = len(paths) if len(paths) < MAX_PATHS else MAX_PATHS
        return sorted(paths, key=lambda x: self.get_path_cost(x))[0:(paths_count)]
