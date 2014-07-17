#ifndef SLIDER_VIEWSIZE_H
#define SLIDER_VIEWSIZE_H

#include <QSlider>

class Slider_Viewsize : public QSlider
{
    Q_OBJECT
public:
    explicit Slider_Viewsize(QWidget *parent = 0);
private:
    void mousePressEvent(QMouseEvent *event);
signals:

public slots:

};

#endif // SLIDER_VIEWSIZE_H
