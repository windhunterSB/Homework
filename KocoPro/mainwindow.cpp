#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GridRowNum = -1;
    GridColumNum = -1;
    GridWidth = 40.0;
    InitGrid(12,12);
    ///MainScene.setSceneRect(0,0,300,300);
    ui->graphicsView->setScene(&MainScene);

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

void MainWindow::InitGrid(int Rows,int Colums)
{
    if(Rows>=0&&Colums>=0){
        GridRowNum = Rows;
        GridColumNum = Colums;
    }
    if(GridRowNum<0||GridColumNum<0) {
        ///error
        QMessageBox::about(this,"FuncName_InitGrid","No_RowNum_or_Columnum");
        return;
    }
    ///else QMessageBox::about(this,"FuncName_InitGrid","Ok!");
    GridRowNum = std::min(GridRowNum,MAXNUM);
    GridColumNum = std::min(GridColumNum,MAXNUM);
    MainScene.clear();
    for(int i=0;i<=GridRowNum;i++){
        MainScene.addLine(0,-GridWidth*i,GridWidth*GridColumNum,-GridWidth*i,QPen(Qt::white,0.2,Qt::DashLine));
    }
    for(int i=0;i<=GridColumNum;i++){
        MainScene.addLine(GridWidth*i,-0,GridWidth*i,-GridWidth*GridRowNum,QPen(Qt::white,0.2,Qt::DashLine));
    }
}
