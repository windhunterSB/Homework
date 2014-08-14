#include "exchangeboard.h"
#include "ui_exchangeboard.h"
#include "mainwindow.h"
#include <QMessageBox>

ExchangeBoard::ExchangeBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExchangeBoard)
{
    ui->setupUi(this);
}

ExchangeBoard::~ExchangeBoard()
{
    delete ui;
}

void ExchangeBoard::on_buttonBox_accepted()
{
    MainWindow *pa = (MainWindow*)parent();
    pa->MyText = ui->textEdit->toPlainText();
}
