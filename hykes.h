#ifndef HYKES_H
#define HYKES_H

#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <cmap.h>
using namespace std;
namespace Ui {
class Hykes;
}

class Hykes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hykes(QWidget *parent = 0);
    ~Hykes();

private:
    Ui::Hykes *ui;
    QPushButton *btn[11][11];       // 棋盘btn
    QList<QPushButton *> chessmanBtn;
    int redMatrix[11][11];
    int blueMatrix[11][11];
    CMap *redMap;
    CMap *blueMap;

    void checkRusult(QPushButton*btn);
    void setRedMatrix(int row, int col);
    void setBlueMatrix(int row, int col);

public slots:
    void onChessmanClick();
    void radioBtnClick();
    void sureBtnClick();
    void resetBtnClick();
};

#endif // HYKES_H
