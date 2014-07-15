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

    void InitGrid(int Rows=-1,int Colums=-1);

private:
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene MainScene;
    QGraphicsScene SmallScene;
    int GridRowNum,GridColumNum;
    double GridWidth,SmallGridWidth;
    double MainToSmallDx,MainToSmallDy,MainToSmallD;
    static const int MAXNUM = 256;///THE MAXNUM OF GridRowNum,GridColumNum

};

#endif // MAINWINDOW_H
