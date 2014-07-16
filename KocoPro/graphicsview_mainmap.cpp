#include "graphicsview_mainmap.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "mainwindow.h"

GraphicsView_Mainmap::GraphicsView_Mainmap(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView_Mainmap::mouseMoveEvent(QMouseEvent *event)
{
    QWidget* cW = parentWidget();
    MainWindow* ui = (MainWindow*)cW->parentWidget();
    ///ui->MainScene.addLine(50,50,100,100,QPen(Qt::red));
    if( event->buttons() & Qt::LeftButton ){
        ;
        ///QMessageBox::about(this,"MainMap","in_gView"++QString::number(event->x())+" , "+QString::number(event->y()));
    }
}

