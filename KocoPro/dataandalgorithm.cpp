#include "dataandalgorithm.h"

qreal Abs(qreal x) {return x>0?x:-x;}

bool SameLocation(QPointF A,QPointF B)
{
    QPointF C = A - B;
#define meps 1e-4
    if(Abs(C.x())<meps&&Abs(C.y())<meps) return true;
    return false;
}

DataAndAlgorithm::DataAndAlgorithm()
{
    __init__();
}

void DataAndAlgorithm::__init__()
{
    clear();
    bitsN = 8;
}

void DataAndAlgorithm::SetBitsN(int bN)
{
    bitsN=bN;
}
void DataAndAlgorithm::clear()
{
    RealPath.clear();
    DDAPath.clear();
    PathPoint.clear();
    Table.clear();
    MainMapLinesItem.clear();
    SmallMapLinesItem.clear();
}

int NearInt(double xx)
{
    if(xx>=0) return (int)(xx+0.5);
    else return (int)(xx-0.5);
}

void DataAndAlgorithm::DDALineFunc(Segment& Seg,vector<QPoint>& Path,vector<QPoint>& Arr,SegmentTable& table)
{
    QPoint StartPoint(Path[0].x(),Path[0].y());
    QPoint EndPoint(NearInt(Seg.End.x()),NearInt(Seg.End.y()));
    QPoint dArr = EndPoint-StartPoint;
    int Jvx = std::abs(dArr.x());
    int Jvy = std::abs(dArr.y());
    int Jrx = 0;
    int Jry = 0;
    int dx,dy,limit=1<<bitsN;
    int ddx = dArr.x()>0?1:-1;
    int ddy = dArr.y()>0?1:-1;
    int lastpos=0;
    table.clear();
    table.push_back(Jvx,Jvy,Jrx,Jry,0,0);
    for(int tim=0;tim<(1<<bitsN);tim++)
    {
        Jrx+=Jvx;
        Jry+=Jvy;
        if(Jrx>=limit) Jrx-=limit,dx=ddx; else dx=0;
        if(Jry>=limit) Jry-=limit,dy=ddy; else dy=0;
        table.push_back(Jvx,Jvy,Jrx,Jry,dx,dy);
        if(dx!=0||dy!=0)
        {
            Arr.push_back(QPoint(dx,dy));
            Path.push_back(QPoint(Path[lastpos].x()+dx,Path[lastpos].y()+dy));
            lastpos++;
        }
    }
}

void DataAndAlgorithm::AddSegment(Segment NewNode)
{
    RealPath.push_back(NewNode);
    vector<QPoint> NPath,NArr;
    SegmentTable Ntable;
    
    int Siz = RealPath.size();
    if(Siz!=1&&SameLocation(NewNode.Start,RealPath[Siz-2].End))///与之前的点一致，起点取过去的终点
    {
        NPath.push_back(*PathPoint[Siz-2].rbegin());
    }
    else///要么第一条线，要么与之前不连续的线，都要新建一个,起点按四舍五入到整点
    {
        NPath.push_back(QPoint(NearInt(NewNode.Start.x()),NearInt(NewNode.Start.y())));
    }
    
    ///start DDA:
    if(NewNode.Lab=='L')
    {///直线插补
        DDALineFunc(NewNode,NPath,NArr,Ntable);
    }
    else///圆弧插补
    {
        ;///???
    }
    DDAPath.push_back(NArr);
    PathPoint.push_back(NPath);
    Table.push_back(Ntable);
}
