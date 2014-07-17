#ifndef GRAPHICSVIEW_SMALLMAP_H
#define GRAPHICSVIEW_SMALLMAP_H

#include <QGraphicsView>

class GraphicsView_Smallmap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView_Smallmap(QWidget *parent = 0);


private:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:

public:
    QRect SceneRect;

};

#endif // GRAPHICSVIEW_SMALLMAP_H
