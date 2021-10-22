#include "MatrixRepository.h"

MatrixRepository::MatrixRepository()
{

}

void MatrixRepository::registerNode(Node *node)
{
    globalMatrix.addNode(node);
}

void MatrixRepository::registerHost(Host *hst)
{
    portMatrix.addNode(hst);
    registerNode(hst);
}

void MatrixRepository::registerLink(Link *ln)
{
    globalMatrix.addLink(ln);
}

void MatrixRepository::registerSwitch(Switch *sw)
{
    graphMatrix.addNode(sw);
    portMatrix.addNode(sw);
    registerNode(sw);
}

void MatrixRepository::registerSSLink(SSLink *ln)
{
    graphMatrix.addLink(ln);
    portMatrix.addLink(ln);
    registerLink(ln);
}

void MatrixRepository::unregisterHost(Host *hst)
{
    portMatrix.removeNode(hst);
    unregisterNode(hst);
}

void MatrixRepository::unregisterNode(Node *node)
{
    globalMatrix.removeNode(node);
}

void MatrixRepository::unregisterLink(Link *ln)
{
    globalMatrix.removeLink(ln);
}

void MatrixRepository::unregisterSwitch(Switch *sw)
{
    graphMatrix.removeNode(sw);
    portMatrix.removeNode(sw);
    unregisterNode(sw);
}

void MatrixRepository::unregisterSSLink(SSLink *ln)
{
    graphMatrix.removeLink(ln);
    portMatrix.removeLink(ln);
    unregisterLink(ln);
}
