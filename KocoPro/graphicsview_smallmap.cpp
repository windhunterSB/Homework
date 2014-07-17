#include "graphicsview_smallmap.h"
#include <QMessageBox>
#include <QGraphicsItem>
#include "ui_mainwindow.h"
#include "mainwindow.h"


GraphicsView_Smallmap::GraphicsView_Smallmap(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView_Smallmap::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && SceneRect.contains(event->pos()) )
    {
        QWidget* cW = parentWidget();
        MainWindow* MW = (MainWindow*)cW->parentWidget();
        QPoint POS = event->pos() - QPoint(MW->MainToSmallDx , MW->MainToSmallDy);

        double KD = MW->GridWidth / MW->SmallGridWidth;
        MW->ChangeView(POS.x()*KD-10 - MW->ViewRect.width()/2 , POS.y()*KD-10 - MW->ViewRect.height()/2 ,
                       MW->ViewRect.width() , MW->ViewRect.height());

        ///QMessageBox::about(this,"SmallMap","in_gView"+QString::number(POS.x())+" , "+QString::number(POS.y()));
    }
}
