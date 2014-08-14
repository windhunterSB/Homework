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
    memset(ErrorCnt,0,sizeof(ErrorCnt));
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
    ///Err Cnt:
    ///ax+by+c=0
    QPointF dA = Seg.End - Seg.Start;
    double a = -dA.y(), b = dA.x();
    double c = -(Seg.Start.x()*a+Seg.Start.y()*b);
    for(int i=0;i<Path.size();i++)
    {
        double x=Path[i].x(),y=Path[i].y();
        double err = Abs(x*a+y*b+c)/sqrt(a*a+b*b);
        int errid = int(err*20);
        if(errid>59) errid=59;
        ErrorCnt[errid]++;
        ///qDebug() << x<<" "<<y<<" : "<<err<<"\n";
    }
}

void DataAndAlgorithm::DDACircleFunc(Segment& Seg,vector<QPoint>& Path,vector<QPoint>& Arr,SegmentTable& table)
///只考虑圆弧在一个象限内的情况，对于圆弧不在一个象限内的，会在MainWindow::AddSegment中自动分割
///数字积分貌似不具备完整的过渡连续象限的能力，真挫 = =！
///圆弧积分加4bits小数位；即取（double值*16向下取整作为结果）
{

    QPoint StartPoint(Path[0].x(),Path[0].y());
    QPoint EndPoint(NearInt(Seg.End.x()),NearInt(Seg.End.y()));
    QPoint dArr = EndPoint-StartPoint;
    int CntX=std::abs(dArr.x());
    int CntY=std::abs(dArr.y());

    int cx = NearInt(Seg.Center.x()*16);
    int cy = NearInt(Seg.Center.y()*16);
    int Jrx = 0;
    int Jry = 0;
    //int xx = std::abs(Path[0].x()*16-cx);
    //int yy = std::abs(Path[0].y()*16-cy);
    int xx = Path[0].x()*16-cx;
    int yy = Path[0].y()*16-cy;
    int dx,dy,limit=1<<(bitsN+4);
    ///Jrx=Jry=limit/2;
    int ddx = dArr.x()>0?1:-1;
    int ddy = dArr.y()>0?1:-1;
    int lastpos=0;
    table.clear();
    int Jvx=yy;
    int Jvy=xx;
    table.push_back(Jvx,Jvy,Jrx,Jry,0,0);
    int tim=0;
    //qDebug() << cx<<" "<<cy<<" : "<<CntX<<" "<<CntY<<"\n";
    while(CntX>0||CntY>0)
    {
        Jvx = yy;
        Jvy = xx;
        Jrx+=Jvx;
        Jry+=Jvy;
        if(Jrx>=limit||Jrx<=-limit) Jrx%=limit,dx=ddx; else dx=0;
        if(Jry>=limit||Jry<=-limit) Jry%=limit,dy=ddy; else dy=0;
        if(CntX==0) Jvx=0,Jrx=0,dx=0;
        if(CntY==0) Jvy=0,Jry=0,dy=0;
        table.push_back(std::abs(Jvx),std::abs(Jvy),std::abs(Jrx),std::abs(Jry),dx,dy);
        if(dx!=0||dy!=0)
        {
            Arr.push_back(QPoint(dx,dy));
            Path.push_back(QPoint(Path[lastpos].x()+dx,Path[lastpos].y()+dy));
            lastpos++;
            if(dx!=0) CntX--,xx+=dx<<4;
            if(dy!=0) CntY--,yy+=dy<<4;
        }
        tim++;
        //if(tim>2000) break;
        //qDebug()<<tim<<" : "<<Jvx<<" , "<<Jvy<<" :: "<<xx<<" , "<<yy<<" :: "<<Jrx<<" "<<Jry<<" :: "<<CntX<<" "<<CntY<<"\n";
    }
    ///Err Cnt:
    ///(x-x0)^2+(y-y0)^2=R^2
    double x0 = Seg.Center.x(), y0 = Seg.Center.y();
    QPointF dA = Seg.Start - Seg.Center;
    double r = sqrt(dA.x()*dA.x()+dA.y()*dA.y());
    for(int i=0;i<Path.size();i++)
    {
        double x=Path[i].x(),y=Path[i].y();
        double err = Abs(sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0))-r);
        int errid = int(err*20);
        if(errid>59) errid=59;
        ErrorCnt[errid]++;
        ///qDebug() << x<<" "<<y<<" : "<<err<<"\n";
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
        int dx = std::abs((double)(NewNode.End.x()-NewNode.Start.x()))+1;
        int dy = std::abs((double)(NewNode.End.y()-NewNode.Start.y()))+1;
        int len = max(dy,dx);
        int bits = 0;
        while((1<<bits)<=len) bits++;
        SetBitsN(bits);
        DDALineFunc(NewNode,NPath,NArr,Ntable);
    }
    else///圆弧插补
    {
        QPointF Arr = NewNode.Start - NewNode.Center;
        int R = sqrt(Arr.x()*Arr.x()+Arr.y()*Arr.y()) + 1;
        int bits = 0;
        while((1<<bits)<=R) bits++;
        SetBitsN(bits);
        DDACircleFunc(NewNode,NPath,NArr,Ntable);
    }
    DDAPath.push_back(NArr);
    PathPoint.push_back(NPath);
    Table.push_back(Ntable);    
}
