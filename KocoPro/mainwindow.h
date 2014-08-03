#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtDebug>
#include <QTextBlock>
#include "dataandalgorithm.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitGrid(int Rows=-1,int Columns=-1,int ox=0,int oy=0);
    void ChangeView(qreal x,qreal y,qreal w,qreal h);

    void AddSegment(Segment NewNode);
    void DealText();
private:
    QPointF MainMapchangeXY(double x,double y);///将坐标点，转变为大地图中的点
    QPointF SmallMapchangeXY(double x,double y);///将坐标点，转变为小地图中的点
public:
    Ui::MainWindow *ui;
    int GridRowNum,GridColumnNum;
    double GridWidth,SmallGridWidth;
    double MainToSmallDx,MainToSmallDy,MainToSmallD;
    static const int MAXNUM = 1000;///THE MAXNUM OF GridRowNum,GridColumNum
    QGraphicsScene MainScene;
    QGraphicsScene SmallScene;

    QRect ViewRect;
    QGraphicsRectItem* SmallViewRect;

    DataAndAlgorithm Data;

    int oX,oY;///X/Y轴在网格中的位置(oX,N-oY)
    double Zoom;///放缩比例尺

    bool TextHighLightFinished;
public slots:
    void ReSizeView(int value);///zoom size Ki = value/100
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_plainTextEdit_textChanged();
};

#endif // MAINWINDOW_H
