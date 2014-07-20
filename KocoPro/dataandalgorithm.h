#ifndef DATAANDALGORITHM_H
#define DATAANDALGORITHM_H

#include "mainwindow.h"
#include <QApplication>
#include <vector>

using namespace std;

struct Segment
{
    QPointF Start,End,Center;
    char Lab;///"L":Line or "C":circle
    char Arr;///"C":Clock or "U":Unclock
    Segment(){}
    Segment(QPointF S,QPointF E,QPointF C,char A):Start(S),End(E),Center(C),Lab('C'),Arr(A){}
    Segment(QPointF S,QPointF E):Start(S),End(E),Lab('L'){}
};


class DataAndAlgorithm
{
public:
    DataAndAlgorithm();

public:
    vector<Segment> Path;
    vector<QPoint>  DDAPath;///{(+-1,0),(0,+-1),(+-1,+-1)}
    ///http://wenku.baidu.com/view/4f053402bed5b9f3f90f1c24.html
};

#endif // DATAANDALGORITHM_H
