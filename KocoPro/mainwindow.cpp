#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GridRowNum = -1;
    GridColumnNum = -1;
    GridWidth = 40.0;
    InitGrid(64,80);

    ui->graphicsView->setScene(&MainScene);
    ui->graphicsView_2->setScene(&SmallScene);///Small map is too small so need to redraw a simple picture
    ///ui->graphicsView_2->setTransform(QTransform().scale(1/1.05,1/1.05));

    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();
    ViewRect = QRect(-10,-10,w-60,h-10);
    ui->graphicsView->setSceneRect(ViewRect);

    SmallViewRect = SmallScene.addRect(MainToSmallDx,MainToSmallDy,(w-30)/GridWidth*SmallGridWidth,(h-10)/GridWidth*SmallGridWidth,QPen(Qt::red));
    ///ui->graphicsView->mapToScene(0,0,100,100);
    ///ui->graphicsView_2->mapToScene(0,0,GridColumNum*GridWidth,GridRowNum*GridWidth);
    ///ui->graphicsView->setBackgroundBrush(QBrush(Qt::red));
    ///ui->graphicsView->show();
    ///MainScene.addLine(150,0,0,150,QPen(Qt::red,3));
    ///MainScene.addRect(100,0,100,100,QPen(Qt::blue,3),QBrush(Qt::yellow));
    ///MainScene.addRect(200,200,500,500,QPen(Qt::red,3),QBrush(Qt::yellow));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGrid(int Rows,int Columns)
{
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

}
/*
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QRect gViewRect = QRect(ui->graphicsView->pos() + ui->centralWidget->pos(),ui->graphicsView->size());///graphicsView's position
    if(gViewRect.contains(event->pos()) && (event->button()==Qt::LeftButton))
    {
        QMessageBox::about(this,"MouseMoveEvent","in_gView");
    }
    else QMessageBox::about(this,"MouseMoveEvent","out_gView : "+QString::number(event->x())+" , "+QString::number(event->y()));
}
*/
