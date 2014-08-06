#include "codebuilder.h"

codebuilder::codebuilder()
{
    __init__();
}

void codebuilder::__init__()
{
    Context.clear();
    BuildLines.clear();
    WainingLines.clear();
}

bool codebuilder::building()
{
    BuildLines.clear();
    WainingLines.clear();
    QPointF LastPos(0,0);
    for(int i=0;i<Context.size();i++)
    {
        QString str = Context[i];
        str = str.replace("\t"," ");///去掉全部tab
        str = str.replace(" ","");///去掉全部 blank
        QRegExp rx_del((QString)"#");
        int endid = str.indexOf(rx_del);
        if(endid==0) continue;
        str = str.left(endid);
        qDebug()<<i<<" "<<str<<" building\n";
        QRegExp rx_null((QString)" +");///null
        int sid = rx_null.indexIn(str);
        int len = rx_null.matchedLength();
        if(sid==0&&len==str.length()) continue;
        if(str.length()==0) continue;
        int lineidx=str.indexOf("Line:");
        int arcidx =str.indexOf("Arc:");
        int fromidx=str.indexOf("from");
        int toidx  =str.indexOf("to");

        bool ok=false;
        if(lineidx!=-1)
        {
            if(fromidx!=-1)///Line:from(,)to(,)
            {
                try{
                    if(str.indexOf("Line:from(")==0)
                    {
                        int s = 10,e = str.indexOf(",",s);
                        double x1 = str.mid(s,e-s).toDouble();
                        s=e+1;e=str.indexOf(")to(",s);
                        double y1 = str.mid(s,e-s).toDouble();
                        s=e+4;e = str.indexOf(",",s);
                        double x2 = str.mid(s,e-s).toDouble();
                        s=e+1;e=str.indexOf(")",s);
                        double y2 = str.mid(s,e-s).toDouble();
                        if(e+1==str.length())
                        {
                            ok=true;
                            QPointF S(x1,y1);
                            QPointF E(x2,y2);
                            BuildLines.push_back(Segment(S,E));
                            qDebug()<<i<<" ok line:"<<x1<<" "<<y1<<" , "<<x2<<" "<<y2<<"\n";
                            LastPos = E;
                        }
                    }
                }
                catch(...)
                {

                }
            }
            else///Line:(,)
            {

            }
        }
        else if(arcidx!=-1)
        {
            if(toidx!=-1)///Arc:(,)from(,)to(,)
            {

            }
            else///Arc:(,)from(,)sweepXXX
            {

            }
        }

        if(!ok)
        {
            WainingLines.push_back(i);
            qDebug()<<"Waring : "<<i<<endl;
            return false;
        }
    }
    return true;
}
/*
Line:from (1,0) to (10,7)
Line: from (6,4) to (10,17)
Line: (-9,-10)
Line:   (8,6)#9090
#90as
   #876
tabtab#987

Line:(-6,11)   #99876
Arc:(0,0) from (5,0) to (0,5) Unclock
Arc :  (10,10) from (20,23) sweep 100  #+-360
*/
