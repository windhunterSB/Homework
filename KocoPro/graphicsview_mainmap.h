#ifndef GRAPHICSVIEW_MAINMAP_H
#define GRAPHICSVIEW_MAINMAP_H

#include <QGraphicsView>

class GraphicsView_Mainmap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView_Mainmap(QWidget *parent = 0);

private:
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // GRAPHICSVIEW_MAINMAP_H
