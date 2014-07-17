#include "graphicsview_mainmap.h"
#include <QMessageBox>
#include <QGraphicsItem>
#include "ui_mainwindow.h"
#include "mainwindow.h"

GraphicsView_Mainmap::GraphicsView_Mainmap(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView_Mainmap::mouseMoveEvent(QMouseEvent *event)
{
    QWidget* cW = parentWidget();
    MainWindow* MW = (MainWindow*)cW->parentWidget();
    ///MW->MainScene.addLine(50,50,100,100,QPen(Qt::red));
    if( event->buttons() & Qt::LeftButton ){

        ///update ViewRect in Scene
        QPoint NowPos(event->pos());
        QPoint Arr = NowPos - LastPos;

        int NX = MW->ViewRect.x()-Arr.x();
        int NY = MW->ViewRect.y()-Arr.y();
        MW->ChangeView(NX,NY,MW->ViewRect.width(),MW->ViewRect.height());

        LastPos = event->pos();
        ///QMessageBox::about(this,"MainMap","in_gView"+QString::number(Arr.x())+" , "+QString::number(Arr.y()));
    }
}

void GraphicsView_Mainmap::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton){
        LastPos = event->pos();
    }
}
