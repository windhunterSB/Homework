#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsItem>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TextHighLightFinished=true;
    GridInitFinished=false;
    Data.clear();
    GridRowNum = -1;
    GridColumnNum = -1;
    GridWidth = 40.0;
    Zoom = 1.0;
    InitGrid(20,20,10,10);



/*
    ui->graphicsView->setScene(&MainScene);
    ui->graphicsView_2->setScene(&SmallScene);///Small map is too small so need to redraw a simple picture
    ///ui->graphicsView_2->setTransform(QTransform().scale(1/1.05,1/1.05));

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    ///ViewRect cannot be NULL
    SmallViewRect = SmallScene.addRect(MainToSmallDx,MainToSmallDy,(w-30)/GridWidth*SmallGridWidth,(h-20)/GridWidth*SmallGridWidth,QPen(Qt::red));

    ChangeView(-10,-10,w-60,h-10);
*/
    ///After ViewRect is created, we can do this
    connect(ui->verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(ReSizeView(int)));

    ///ui->graphicsView->mapToScene(0,0,100,100);
    ///ui->graphicsView_2->mapToScene(0,0,GridColumNum*GridWidth,GridRowNum*GridWidth);
    ///ui->graphicsView->setBackgroundBrush(QBrush(Qt::red));
    ///ui->graphicsView->show();
    ///MainScene.addLine(150,0,0,150,QPen(Qt::red,3));
    ///MainScene.addRect(100,0,100,100,QPen(Qt::blue,3),QBrush(Qt::yellow));
    ///MainScene.addRect(200,200,500,500,QPen(Qt::red,3),QBrush(Qt::yellow));

    ///Line:Test
    //AddSegment(Segment(QPointF(0,0),QPointF(50,10)));
    //AddSegment(Segment(QPointF(50,10),QPointF(40,-10)));
    //AddSegment(Segment(QPointF(40,-10),QPointF(0,0)));
    //AddSegment(Segment(QPointF(-20,0),QPointF(70,50)));
    ///Circle:Test
    //AddSegment(Segment(QPointF(5,0),QPointF(0,5),QPointF(0,0),'U'));
    //AddSegment(Segment(QPointF(0,10),QPointF(0,-10),QPointF(0,0),'U'));
    //AddSegment(Segment(QPointF(0,15),QPointF(0,-15),QPointF(0,0),'C'));
    //AddSegment(Segment(QPointF(-20,-20),QPointF(12,-16)));
    //AddSegment(Segment(QPointF(12,-16),QPointF(-16,12),QPointF(0,0),'U'));
    //AddSegment(Segment(QPointF(-16,12),QPointF(-20,-20)));
    //AddSegment(Segment(QPointF(24,-32),QPointF(-32,24),QPointF(0,0),'C'));
    //AddSegment(Segment(QPointF(54,-62),QPointF(-62,54),QPointF(30,30),'U'));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGrid(int Rows,int Columns,int ox,int oy)
{
    GridInitFinished=false;
    Data.clear();
    Zoom=1;

    if(Rows>=0&&Columns>=0){
        GridRowNum = Rows;
        GridColumnNum = Columns;
    }
    if(GridRowNum<=0||GridColumnNum<=0) {
        ///error
        QMessageBox::about(this,"FuncName_InitGrid","No_RowNum_or_Columnum");
        return;
    }
    ///else QMessageBox::about(this,"FuncName_InitGrid","Ok!");
    GridRowNum = std::min(GridRowNum,MAXNUM);
    GridColumnNum = std::min(GridColumnNum,MAXNUM);
    MainScene.clear();
    for(int i=0;i<=GridRowNum;i++){
        MainScene.addLine(0,GridWidth*i,GridWidth*GridColumnNum,GridWidth*i,QPen(Qt::white,1.0,Qt::DashLine));
    }
    for(int i=0;i<=GridColumnNum;i++){
        MainScene.addLine(GridWidth*i,0,GridWidth*i,GridWidth*GridRowNum,QPen(Qt::white,1.0,Qt::DashLine));
    }
    oX=ox;oY=oy;
    MainScene.addLine(0,GridWidth*(GridRowNum-oY),GridWidth*GridColumnNum,GridWidth*(GridRowNum-oY),QPen(Qt::white,3.0,Qt::SolidLine));
    MainScene.addLine(GridWidth*oX,0,GridWidth*oX,GridWidth*GridRowNum,QPen(Qt::white,3.0,Qt::SolidLine));

    SmallScene.clear();
    double w = ui->graphicsView_2->width();
    double h = ui->graphicsView_2->height();
    double dw = w/GridColumnNum;
    double dh = h/GridRowNum;
    double dd = std::min(dw,dh) / 1.05;

    SmallGridWidth = dd;
    MainToSmallDx = ( w - dd*GridColumnNum )/2;
    MainToSmallDy = ( h - dd*GridRowNum   )/2;
    MainToSmallD  = dd/GridWidth;

    double L = MainToSmallDx, R = MainToSmallDx+GridColumnNum*dd;
    double U = MainToSmallDy, D = MainToSmallDy+GridRowNum*dd;
    SmallScene.addLine(L,U,R,U,QPen(Qt::white,1.0,Qt::SolidLine));
    SmallScene.addLine(L,D,R,D,QPen(Qt::white,1.0,Qt::SolidLine));
    SmallScene.addLine(L,U,L,D,QPen(Qt::white,1.0,Qt::SolidLine));
    SmallScene.addLine(R,U,R,D,QPen(Qt::white,1.0,Qt::SolidLine));

    SmallScene.addLine(L,U+(GridRowNum-oY)*dd,R,U+(GridRowNum-oY)*dd,QPen(Qt::white,1.0,Qt::SolidLine));
    SmallScene.addLine(L+oX*dd,U,L+oX*dd,D,QPen(Qt::white,1.0,Qt::SolidLine));

    ui->graphicsView_2->SceneRect = QRect(L,U,R-L,D-U);
    ui->graphicsView_2->setSceneRect(QRect(L,U,R-L,D-U));


    ui->graphicsView->setScene(&MainScene);
    ui->graphicsView_2->setScene(&SmallScene);///Small map is too small so need to redraw a simple picture
    ///ui->graphicsView_2->setTransform(QTransform().scale(1/1.05,1/1.05));

    int ww = ui->graphicsView->width();
    int hh = ui->graphicsView->height();

    ///ViewRect cannot be NULL
    SmallViewRect = SmallScene.addRect(MainToSmallDx,MainToSmallDy,(ww-30)/GridWidth*SmallGridWidth,(hh-20)/GridWidth*SmallGridWidth,QPen(Qt::red));

    ChangeView(-10,-10,ww-60,hh-10);
    GridInitFinished=true;

    ReSizeView(ui->verticalSlider->value());
    //ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::ChangeView(qreal x,qreal y,qreal w,qreal h)
{
    double Ki = h / (ui->graphicsView->height()-10 ) ;

    x = std::min(x,(qreal)( GridColumnNum   * GridWidth - w ));
    y = std::min(y,(qreal)( GridRowNum * GridWidth - h)+20);
    x = std::max(x, (qreal)-20);///because ( MW->GridRowNum    * MW->GridWidth - MW->ViewRect.width() ) maybe smaller than 0
    y = std::max(y, (qreal)-20);

    ///Main map:
    ViewRect = QRect(x,y,w,h);
    ui->graphicsView->setSceneRect(ViewRect);
    ui->graphicsView->resetTransform();
    ui->graphicsView->setTransform(QTransform().scale(1/Ki,1/Ki));

    ///Small map:
    double DK = GridWidth / SmallGridWidth;
    SmallViewRect->setRect((x+20)/DK + MainToSmallDx,(y+20)/DK + MainToSmallDy,
                               (w-25)/DK,(h-20)/DK);
}

void MainWindow::ReSizeView(int value)
{
    double Ki  = (double)value/200.0;
    Zoom = 1.0/Ki;
    qreal nx,ny,nw,nh;
    try
    {
        nx = ViewRect.x();
        ny = ViewRect.y();
        nw = ViewRect.width();
        nh = ViewRect.height();

        Ki *= nh / (ui->graphicsView->height()-10 ) ;

        nx = nx + nw/2 - nw/2/Ki;
        ny = ny + nh/2 - nh/2/Ki;
        nw /= Ki;
        nh /= Ki;
        ChangeView(nx,ny,nw,nh);
    }
    catch(...)
    {
        return;
    }
}

QPointF MainWindow::MainMapchangeXY(double x,double y)///将坐标点，转变为大地图中的点
{
    double xx = (x+oX)*GridWidth;
    double yy = ((double)GridRowNum - y-oY)*GridWidth;
    return QPointF(xx,yy);
}

QPointF MainWindow::SmallMapchangeXY(double x,double y)
{
    double xx = (x+oX)*SmallGridWidth + MainToSmallDx;
    double yy = ((double)GridRowNum - y-oY)*SmallGridWidth + MainToSmallDy ;
    return QPointF(xx,yy);
}

void MainWindow::AddSegment(Segment NewNode)
{
    SegmentLineItem MainItem,SmallItem;

    if(NewNode.Lab=='L')
    {
        Data.AddSegment(NewNode);
        QPointF S = MainMapchangeXY(NewNode.Start.x(),NewNode.Start.y()),E = MainMapchangeXY(NewNode.End.x(),NewNode.End.y());
        MainItem.RealLine = MainScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(0,162,232),5.0,Qt::SolidLine));
        S = SmallMapchangeXY(NewNode.Start.x(),NewNode.Start.y()),E = SmallMapchangeXY(NewNode.End.x(),NewNode.End.y());
        SmallItem.RealLine = SmallScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(0,162,232),1.0,Qt::SolidLine));
        int pos = (int)Data.PathPoint.size() - 1;
        int siz = (int)Data.PathPoint[pos].size() -1;
        for(int i=0;i<siz;i++)
        {
            S = MainMapchangeXY(Data.PathPoint[pos][i].x()  ,Data.PathPoint[pos][i].y());
            E = MainMapchangeXY(Data.PathPoint[pos][i+1].x(),Data.PathPoint[pos][i+1].y());
            QGraphicsItem* Maintmp = MainScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(34,177,76),4.0,Qt::SolidLine));
            MainItem.CaluLine.push_back(Maintmp);
            S = SmallMapchangeXY(Data.PathPoint[pos][i].x()  ,Data.PathPoint[pos][i].y());
            E = SmallMapchangeXY(Data.PathPoint[pos][i+1].x(),Data.PathPoint[pos][i+1].y());
            QGraphicsItem* Smalltmp = SmallScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(34,177,76),1.0,Qt::SolidLine));
            SmallItem.CaluLine.push_back(Smalltmp);
        }
    }
    else
    {
        ///象限检测+分割
        QPointF SS = NewNode.Start-NewNode.Center,EE = NewNode.End-NewNode.Center;
        double thetaS=atan2(SS.y(),SS.x());
        double thetaE=atan2(EE.y(),EE.x());
        double pi = acos(-1.0);
        double eps = 1e-6;
        double R = sqrt(SS.x()*SS.x()+SS.y()*SS.y());
        vector<Segment> CirVec;
        if(NewNode.Arr=='U')
        {
            if(thetaS-thetaE>-eps)///过180度边界
                thetaE+=2*pi;
            for(int id=-2;id<8;id++)
            {
                double cut1 = pi/2*(double)id;
                double cut2 = pi/2*(double)(id+1);
                cut1 = std::max(cut1,thetaS);
                cut2 = std::min(cut2,thetaE);
                if(cut1+eps<cut2)
                {
                    Segment NewSeg = NewNode;
                    NewSeg.Start = QPointF(cos(cut1)*R,sin(cut1)*R)+NewNode.Center;
                    NewSeg.End   = QPointF(cos(cut2)*R,sin(cut2)*R)+NewNode.Center;
                    CirVec.push_back(NewSeg);
                }
            }
        }
        else
        {
            if(thetaE-thetaS>-eps)///过180度边界
                thetaS+=2*pi;
            for(int id=7;id>=-2;id--)
            {
                double cut1 = pi/2*(double)id;
                double cut2 = pi/2*(double)(id+1);
                cut1 = std::max(cut1,thetaE);
                cut2 = std::min(cut2,thetaS);
                if(cut1+eps<cut2)
                {
                    Segment NewSeg = NewNode;
                    NewSeg.Start = QPointF(cos(cut2)*R,sin(cut2)*R)+NewNode.Center;
                    NewSeg.End   = QPointF(cos(cut1)*R,sin(cut1)*R)+NewNode.Center;
                    CirVec.push_back(NewSeg);
                }
            }
        }

        for(int i=0;i<(int)CirVec.size();i++)
        {

            Data.AddSegment(CirVec[i]);
            SS = CirVec[i].Start-CirVec[i].Center;
            EE = CirVec[i].End - CirVec[i].Center;
            double tS=0 - atan2(SS.y(),SS.x())/pi*180;
            double tE=0 - atan2(EE.y(),EE.x())/pi*180;
            double Sweep = 0;
            if(NewNode.Arr=='U') std::swap(tS,tE);
            if(tE<tS-eps) tE+=360;
            Sweep = tE - tS;
            if(tS<0) tS+=360;
            QPainterPath MainPath,SmallPath;
            QPointF LU = NewNode.Center - QPointF(R,R),RD = NewNode.Center + QPointF(R,R);
            QPointF StartP=NewNode.Arr=='U'?MainMapchangeXY(CirVec[i].End.x(),CirVec[i].End.y()):MainMapchangeXY(CirVec[i].Start.x(),CirVec[i].Start.y());
            MainPath.moveTo(StartP);
            QPointF MainLU = MainMapchangeXY(LU.x(),LU.y()),MainRD = MainMapchangeXY(RD.x(),RD.y());
            MainPath.arcTo(MainLU.x(),MainLU.y(),MainRD.x()-MainLU.x(),MainRD.y()-MainLU.y(),tS,Sweep);
            //qDebug()<<MainLU.x()<<" "<<MainLU.y()<<" "<<MainRD.x()-MainLU.x()<<" "<<MainRD.y()-MainLU.y()<<" | "<<tS<<" "<<Sweep<<"\n";
            //MainPath.moveTo(55+cos(atan2(SS.y(),SS.x())*45),55+sin(atan2(SS.y(),SS.x()))*45);
            //MainPath.arcTo((qreal)10,(qreal)10,(qreal)100,(qreal)100,(qreal)tS,(qreal)Sweep);
            MainItem.RealLine = MainScene.addPath(MainPath,QPen(QColor(0,162,232),5.0,Qt::SolidLine));

            QPointF SmallLU = SmallMapchangeXY(LU.x(),LU.y()),SmallRD = SmallMapchangeXY(RD.x(),RD.y());
            StartP=NewNode.Arr=='U'?SmallMapchangeXY(CirVec[i].End.x(),CirVec[i].End.y()):SmallMapchangeXY(CirVec[i].Start.x(),CirVec[i].Start.y());
            SmallPath.moveTo(StartP);
            SmallPath.arcTo(SmallLU.x(),SmallLU.y(),SmallRD.x()-SmallLU.x(),SmallRD.y()-SmallLU.y(),tS,Sweep);
            SmallItem.RealLine = SmallScene.addPath(SmallPath,QPen(QColor(0,162,232),1.0,Qt::SolidLine));

            int pos = (int)Data.PathPoint.size() - 1;
            int siz = (int)Data.PathPoint[pos].size() -1;
            QPointF S,E;

            for(int i=0;i<siz;i++)
            {
                S = MainMapchangeXY(Data.PathPoint[pos][i].x()  ,Data.PathPoint[pos][i].y());
                E = MainMapchangeXY(Data.PathPoint[pos][i+1].x(),Data.PathPoint[pos][i+1].y());
                QGraphicsItem* Maintmp = MainScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(34,177,76),4.0,Qt::SolidLine));
                MainItem.CaluLine.push_back(Maintmp);
                S = SmallMapchangeXY(Data.PathPoint[pos][i].x()  ,Data.PathPoint[pos][i].y());
                E = SmallMapchangeXY(Data.PathPoint[pos][i+1].x(),Data.PathPoint[pos][i+1].y());
                QGraphicsItem* Smalltmp = SmallScene.addLine(S.x(),S.y(),E.x(),E.y(),QPen(QColor(34,177,76),1.0,Qt::SolidLine));
                SmallItem.CaluLine.push_back(Smalltmp);
            }

        }

    }

    Data.MainMapLinesItem.push_back(MainItem);
    Data.SmallMapLinesItem.push_back(SmallItem);

    int TableId = Data.Table.size()-1;
    int Siz = (int)Data.Table[TableId].Jvx.size();
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row+1);
    QTableWidget* table = ui->tableWidget;
    for(int c=0;c<6;c++)
    {
        QTableWidgetItem* LineHehe= new QTableWidgetItem;
        switch(c)
        {
            case 0:LineHehe->setText("New");break;
            case 1:LineHehe->setText("Line");break;
            case 2:LineHehe->setText(":");break;
            case 3:LineHehe->setText("...");break;
            case 4:LineHehe->setText("...");break;
            case 5:LineHehe->setText("...");break;
        }


        table->setItem(row, c, LineHehe);
    }
    for(int i=0;i<Siz;i++)
    {
        row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row+1);
        QTableWidgetItem *itemJrx, *itemJvx,*itemDx,*itemJry, *itemJvy,*itemDy;
        itemJrx = new QTableWidgetItem;
        itemJvx = new QTableWidgetItem;
        itemDx = new QTableWidgetItem;
        itemJry = new QTableWidgetItem;
        itemJvy = new QTableWidgetItem;
        itemDy = new QTableWidgetItem;



        QString txt = QString("%1").arg(Data.Table[TableId].Jrx[i]);
        itemJrx->setText(txt);
        table->setItem(row, 0, itemJrx);

        txt = QString("%1").arg(Data.Table[TableId].Jvx[i]);
        itemJvx->setText(txt);
        table->setItem(row, 1, itemJvx);

        switch(Data.Table[TableId].dX[i])
        {
            case -1: txt="-1";break;
            case 0: txt="";break;
            case 1: txt="+1";break;
        }
        itemDx->setText(txt);
        table->setItem(row, 2, itemDx);

        txt = QString("%1").arg(Data.Table[TableId].Jry[i]);
        itemJry->setText(txt);
        table->setItem(row, 3, itemJry);

        txt = QString("%1").arg(Data.Table[TableId].Jvy[i]);
        itemJvy->setText(txt);
        table->setItem(row, 4, itemJvy);

        switch(Data.Table[TableId].dY[i])
        {
            case -1: txt="-1";break;
            case 0: txt="";break;
            case 1: txt="+1";break;
        }
        itemDy->setText(txt);
        table->setItem(row, 5, itemDy);

        qDebug()<<"row "<<row<<"\n";
    }
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::about(this,"hehe","clicked");
    codebuilder CODE;
    CODE.__init__();
    QTextDocument* Doc = ui->plainTextEdit->document();
    for(QTextBlock bk = Doc->begin();bk!=Doc->end();bk=bk.next())///取出每一行,以\n为分割
    {
        CODE.Context.push_back(bk.text());
    }
    bool canbuild = CODE.building();
    if(canbuild)
    {
        int aU=10,aD=-10,aL=-10,aR=10;
        for(int i=0;i<(int)CODE.BuildLines.size();i++)
        {
            if(CODE.BuildLines[i].Lab=='L')
            {
                aU=max(aU,(int)max(CODE.BuildLines[i].Start.y(),CODE.BuildLines[i].End.y())+4 );
                aD=min(aD,(int)min(CODE.BuildLines[i].Start.y(),CODE.BuildLines[i].End.y())-4 );
                aL=min(aL,(int)min(CODE.BuildLines[i].Start.x(),CODE.BuildLines[i].End.x())-4 );
                aR=max(aR,(int)max(CODE.BuildLines[i].Start.x(),CODE.BuildLines[i].End.x())+4 );
            }
            else
            {
                QPointF Arr = CODE.BuildLines[i].Start - CODE.BuildLines[i].Center;
                double R = sqrt(Arr.x()*Arr.x()+Arr.y()*Arr.y());
                aU=max(aU,(int)(CODE.BuildLines[i].Center.y()+R)+4);
                aD=min(aD,(int)(CODE.BuildLines[i].Center.y()-R)-4);
                aL=min(aL,(int)(CODE.BuildLines[i].Center.x()-R)-4);
                aR=max(aR,(int)(CODE.BuildLines[i].Center.x()+R)+4);
            }
        }
        InitGrid(aU-aD,aR-aL,-aL,-aD);///需要修正

        for(int i=0;i<(int)(CODE.BuildLines.size());i++)
        {
            AddSegment(CODE.BuildLines[i]);
        }
    }
    else
    {
        ///显示错误行

        int warningLine = CODE.WainingLines[0];
        QTextDocument* Doc = ui->plainTextEdit->document();
        QTextCursor Cursor(Doc);
        Cursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,warningLine);
        Cursor.insertText("Warning: ");

        //qDebug()<<"WarningColor:: Line:"<<warningLine<<endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::DealText()
{
    QTextDocument* Doc = ui->plainTextEdit->document();
    QTextCursor Cursor(Doc);
    QTextCharFormat plainFormat(Cursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    plainFormat.setForeground(QColor(231,231,231));

    Cursor.movePosition(QTextCursor::End,QTextCursor::KeepAnchor);
    Cursor.mergeCharFormat(plainFormat);
    QString stset[10] = {"Line","Arc","from","to","sweep","#","Warning"};
    for(int i=0;i<7;i++){
        if(i<2) colorFormat.setForeground(QColor(0,162,232));
        else if(i<5)    colorFormat.setForeground(QColor(162,162,0));
        else if(i<6) colorFormat.setForeground(QColor(0,200,30));
        else colorFormat.setForeground(QColor(231,80,0));
        QTextCursor highlightCursor(Doc);
        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            if(i<5) highlightCursor = Doc->find(stset[i], highlightCursor,QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
            else    highlightCursor = Doc->find(stset[i], highlightCursor,QTextDocument::FindCaseSensitively);

            if (!highlightCursor.isNull()) {
                //highlightCursor.movePosition(QTextCursor::WordRight,QTextCursor::KeepAnchor);//会产生abc::连带“：：”也被选中的情况
                //highlightCursor.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor,0);//不加也行
                if(i<5) highlightCursor.mergeCharFormat(colorFormat);
                else {
                    highlightCursor.movePosition(QTextCursor::EndOfBlock,QTextCursor::KeepAnchor);
                    highlightCursor.mergeCharFormat(colorFormat);
                }
            }
        }
    }
    TextHighLightFinished=true;
}


void MainWindow::on_plainTextEdit_textChanged()
///文本改变时发生
{
    if(TextHighLightFinished) {TextHighLightFinished=false;DealText();}
}
