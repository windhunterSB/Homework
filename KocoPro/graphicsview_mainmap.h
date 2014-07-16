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
    ///void mousePressEvent(QMouseEvent *event);
    ///void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint LastPos;

signals:

public slots:

};

#endif // GRAPHICSVIEW_MAINMAP_H
