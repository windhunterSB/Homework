#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitGrid(int Rows=-1,int Columns=-1);

public:
    Ui::MainWindow *ui;
    int GridRowNum,GridColumnNum;
    double GridWidth,SmallGridWidth;
    double MainToSmallDx,MainToSmallDy,MainToSmallD;
    static const int MAXNUM = 256;///THE MAXNUM OF GridRowNum,GridColumNum
    QGraphicsScene MainScene;
    QGraphicsScene SmallScene;
    QRect ViewRect;

};

#endif // MAINWINDOW_H
