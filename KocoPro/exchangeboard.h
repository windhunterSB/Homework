#ifndef EXCHANGEBOARD_H
#define EXCHANGEBOARD_H

#include <QDialog>

namespace Ui {
class ExchangeBoard;
}

class ExchangeBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeBoard(QWidget *parent = 0);
    ~ExchangeBoard();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ExchangeBoard *ui;
};

#endif // EXCHANGEBOARD_H
