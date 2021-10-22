#ifndef NETWORKMAPVIEW_H
#define NETWORKMAPVIEW_H

#include <QLabel>
#include <QMouseEvent>

class NetworkMapView : public QLabel
{
    Q_OBJECT

public:
    explicit NetworkMapView(QWidget *parent = 0);
    void refresh(QPixmap);

private:
    void initialize();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void signalMouseLeftButtonReleased(QPoint cursorPosition);
    void signalMouseLeftButtonPressed(QPoint cursorPosition);
    void signalMouseMoved(QPoint cursorPosition);
    void signalMouseDoubleClicked(QPoint cursorPosition);
};

#endif // NETWORKMAPVIEW_H
