#ifndef DATAANDALGORITHM_H
#define DATAANDALGORITHM_H

#include <QApplication>
#include <vector>
#include <QGraphicsScene>
#include <QtDebug>

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

struct SegmentTable
{
    vector<int> Jvx,Jrx;
    vector<int> Jvy,Jry;
    vector<int> dX,dY;
    void clear()
    {
        Jvx.clear();Jrx.clear();
        Jvy.clear();Jry.clear();
        dX.clear();dY.clear();
    }
    void push_back(int jvx,int jvy,int jrx,int jry,int dx,int dy)
    {
        Jvx.push_back(jvx);Jrx.push_back(jrx);
        Jvy.push_back(jvy);Jry.push_back(jry);
        dX.push_back(dx);dY.push_back(dy);
    }
};

struct SegmentLineItem
{
    QGraphicsItem* RealLine;///line or circle
    vector<QGraphicsItem*> CaluLine;
};


class DataAndAlgorithm
{
public:
    DataAndAlgorithm();
private:
    void __init__();
    void SetBitsN(int bN);
    void DDALineFunc(Segment& Seg,vector<QPoint>& Path,vector<QPoint>& Arr,SegmentTable& table);
    void DDACircleFunc(Segment& Seg,vector<QPoint>& Path,vector<QPoint>& Arr,SegmentTable& table);
public:
    int bitsN;
    vector<Segment> RealPath;
    vector<vector<QPoint> >  DDAPath;///{(+-1,0),(0,+-1),(+-1,+-1)}
    vector<vector<QPoint> >  PathPoint;///PathPoint[i] = DDAPath[i-1] + PathPoint[i-1]
    vector<SegmentTable> Table;
    vector<SegmentLineItem> MainMapLinesItem,SmallMapLinesItem;
    ///http://wenku.baidu.com/view/4f053402bed5b9f3f90f1c24.html
public:
    void AddSegment(Segment NewNode);
    void clear();
};

#endif // DATAANDALGORITHM_H
