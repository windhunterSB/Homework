#include "slider_viewsize.h"
#include <QMessageBox>
#include <QGraphicsItem>
#include "ui_mainwindow.h"
#include "mainwindow.h"

Slider_Viewsize::Slider_Viewsize(QWidget *parent) :
    QSlider(parent)
{
    setValue(maximum());
}

void Slider_Viewsize::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);///without it -> cannot move!
    if(event->button() == Qt::LeftButton)
    {
        double pos = event->pos().y() / (double)height();
        setValue(maximum() - pos * (maximum() - minimum()) );
    }
}
