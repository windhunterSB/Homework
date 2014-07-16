#include "graphicsview_mainmap.h"
#include <QMessageBox>
#include "ui_mainwindow.h"

GraphicsView_Mainmap::GraphicsView_Mainmap(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView_Mainmap::mouseMoveEvent(QMouseEvent *event)
{
    if( event->button()==Qt::LeftButton)
    {
        QMessageBox::about(this,"MainMap","in_gView");
    }
    else QMessageBox::about(this,"MainMap","out_gView : "+QString::number(event->x())+" , "+QString::number(event->y()));
}
