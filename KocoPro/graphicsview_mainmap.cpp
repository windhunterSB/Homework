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

        NX = std::min(NX,(int)( MW->GridColumnNum   * MW->GridWidth - MW->ViewRect.width() ));
        NY = std::min(NY,(int)( MW->GridRowNum * MW->GridWidth - MW->ViewRect.height())+20);
        NX = std::max(NX, -10);///because ( MW->GridRowNum    * MW->GridWidth - MW->ViewRect.width() ) maybe smaller than 0
        NY = std::max(NY, -10);
        MW->ViewRect = QRect(NX,NY,MW->ViewRect.width(),MW->ViewRect.height());
        setSceneRect(MW->ViewRect);
        LastPos = event->pos();
        ///QMessageBox::about(this,"MainMap","in_gView"+QString::number(Arr.x())+" , "+QString::number(Arr.y()));

        ///Small Map:
        double DK = MW->GridWidth / MW->SmallGridWidth;
        MW->SmallViewRect->setRect((NX+10)/DK + MW->MainToSmallDx,(NY+10)/DK + MW->MainToSmallDy,
                                   (MW->ViewRect.width()-30)/DK,(MW->ViewRect.height()-10)/DK);
    }
}

void GraphicsView_Mainmap::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton){
        LastPos = event->pos();
    }
}
