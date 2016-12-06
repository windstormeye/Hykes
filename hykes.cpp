#include "hykes.h"
#include "ui_hykes.h"
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <iostream>
#include <QCursor>
#include <QRadioButton>
#include <QPushButton>
using namespace std;
// 设置一个判断棋色的静态全局变量
static bool isRed;
static bool isSure;
static bool isAgain;


// 构造函数
Hykes::Hykes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hykes)
{
    ui->setupUi(this);

    // 初始化图
    redMap = new CMap(11);
    blueMap = new CMap(11);

    // 设置两个选择按钮
    QRadioButton *radioBtn1 = new QRadioButton("红方先手", this);
    radioBtn1->setStyleSheet({"color:rgb(255,0,0)"});
    radioBtn1->setFont(QFont());
    radioBtn1->setGeometry(QRect(700,30,100,30));
    radioBtn1->setChecked(true);
    connect(radioBtn1, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));

    QRadioButton *radioBtn2 = new QRadioButton("蓝方先手", this);
    radioBtn2->setStyleSheet({"color:rgb(0,0,255)"});
    radioBtn2->setGeometry(QRect(700,60,100,30));
    connect(radioBtn2, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));


    QPushButton *sureBtn = new QPushButton(this);
    sureBtn->setText("确定");
    sureBtn->setGeometry(QRect(800,45,50,30));
    connect(sureBtn, SIGNAL(clicked(bool)), this, SLOT(sureBtnClick()));

    QPushButton *resetBtn = new QPushButton(this);
    resetBtn->setText("重置棋盘");
    resetBtn->setGeometry(QRect(700, 200, 80 ,30));
    connect(resetBtn, SIGNAL(clicked(bool)), this, SLOT(resetBtnClick()));

    // 设置窗体初始化大小
    this->resize(QSize(900, 550));
    // 设置窗体初始化坐标
    this->move(QPoint(300,200));
    // 双循环创建棋盘
    for(int i = 1; i <= 11; i++)
    {
        for(int j = 1; j <= 11; j++)
        {
            btn[i-1][j-1] = new QPushButton(this);
            btn[i-1][j-1]->setStyleSheet("border-image: url(:/new/prefix1/000.png);");
            btn[i-1][j-1]->setGeometry(70 + ((j-1) * 40) + ((i-1) * 20),51 + ((i-1) * 37) ,40 ,50);
            btn[i-1][j-1]->show();

            QString str = QString::number(btn[i-1][j-1]->pos().x()).append(QString::number(btn[i-1][j-1]->pos().y()));

            connect(btn[i-1][j-1], SIGNAL(clicked()), this, SLOT(onChessmanClick()));
        }
   }
    // 初始化先让红方先走
    isRed = true;
    isSure = false;
    isAgain = false;
}

Hykes::~Hykes()
{
    delete ui;
}

void Hykes::sureBtnClick()
{
    if(!isAgain)
    {
        if(!isSure)
        {
            isSure = true;
            isAgain = true;
        }
    }
    else
    {
        QMessageBox::information(this, "错误", "已选择过先手", QMessageBox::Ok);
    }
}

void Hykes::radioBtnClick()
{
    if(!isSure)
    {
        isRed = !isRed;
    }
}

void Hykes::resetBtnClick()
{
    for(int i = 0; i < chessmanBtn.size(); i++)
    {
       chessmanBtn[i]->setStyleSheet("border-image: url(:/new/prefix1/000.png);");
       chessmanBtn[i]->setEnabled(true);
       chessmanBtn[i]->setText("");
    }
}

void Hykes::onChessmanClick()
{
    // 获取鼠标点击坐标
//    QPoint point = QCursor::pos();
    // QObject::sender( ) 返回发送信号的对象的指针，返回类型为QObject* 。可使用qobject_cast动态类型转换成对应的发送信息的对象（对象类的基类中需要有QObject）
    QPushButton*btn = qobject_cast<QPushButton*>(sender());//获取发射信号的对象，并且向下转型为QPushButton


    if(isSure)
    {
        chessmanBtn.push_back(btn);

        int y = (btn->pos().y() - 51) / 37;
        int x = ((btn->pos().x() - 70) - (y * 20)) / 40;


//        btn->setText(QString::number(x,10) +"-"+ QString::number(y, 10));
        if(isRed)
        {
            btn->setStyleSheet("border-image: url(:/new/prefix1/111.png);");
            // 点击后让按钮变成不可点击的状态
            redMap->setValueToMatrixForUndirectedGraph(x, y);
            redMap->printMatrix();
            cout << "red" << endl;
            btn->setEnabled(false);
        }
        else
        {
            btn->setStyleSheet("border-image: url(:/new/prefix1/222.png);");
            // 点击后让按钮变成不可点击的状态
            blueMap->setValueToMatrixForUndirectedGraph(x, y);
            blueMap->printMatrix();
            cout << "blue" <<endl;
            btn->setEnabled(false);
        }
            // 让按钮的点击事件触发后，isRed取反
            isRed = !isRed;
    }
    else
    {
        QMessageBox::information(this, "错误", "请先选择选择红或蓝方先手", QMessageBox::Ok);
    }
}

void Hykes::checkRusult(QPushButton*btn)
{
    QString str = QString::number(btn->pos().x()).append(QString::number(btn->pos().y()));
}

void Hykes::setRedMatrix(int row, int col)
{
    redMatrix[row][col] = 1;
    std::cout << redMatrix[row][col] << "r   ";
}

void Hykes::setBlueMatrix(int row, int col)
{
    blueMatrix[row][col] = 1;
    std::cout << blueMatrix[row][col] << "b   ";
}


// Qt必须在paintEvent方法中绘图，在此重载该函数
void QWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;

    QBrush bruch(Qt::SolidPattern);//画刷
    bruch.setColor(Qt::red);

    int i = 11;
    int j = 0;
    // 循环画下边红色部分的三角形
    while (i--)
    {
        QPolygonF polygon;
        polygon << QPointF(290 + (j * 40), 471) << QPointF(310 + (j * 40), 459) << QPointF(330 + (j * 40), 471);//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);

        j++;
    }
    i = 11;
    j = 0;
    // 循环画上边的红色三角形
    while (i--)
    {
        QPolygonF polygon;
        polygon << QPointF(50 + (j * 40), 51) << QPointF(70 + (j * 40), 63) << QPointF(90 + (j * 40), 51);//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);

        j++;
    }
    // 画一个上边的三分之一长度三角形
    QPolygonF polygon1;
    polygon1 << QPointF(50 + (j * 40), 51) << QPointF(70 + (j * 40), 63) << QPointF(65 + (j * 40), 51);//顺时针取点
    painter.setPen(pen);
    painter.setBrush(bruch);
    painter.drawPolygon(polygon1, Qt::WindingFill);


    // 重新定义一个画刷
    bruch.setColor(Qt::blue);
    int n = 11;
    int m = 0;
    // 循环画左边蓝色三角形
    while (n--)
    {
        QPolygonF polygon;
        polygon << QPointF(50 + (m * 20), 52 + (m * 37)) << QPointF(70 + (m * 20), 89 + (m * 37)) << QPointF(70 + (m * 20), 64 + (m * 37));//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);

        m++;
    }
    // 画左下角三分之一个三角形
    QPolygonF polygon;
    polygon << QPointF(50 + (m * 20), 52 + (m * 37)) << QPointF(56 + (m * 20), 64 + (m * 37)) << QPointF(70 + (m * 20), 64 + (m * 37));//顺时针取点
    painter.setPen(pen);
    painter.setBrush(bruch);
    painter.drawPolygon(polygon, Qt::WindingFill);

    n = 11;
    m = 0;
    // 循环画右边蓝色三角形
    while (n--)
    {
        QPolygonF polygon;
        polygon << QPointF(510 + (m * 20), 63 + (m * 37)) << QPointF(530 + (m * 20), 100 + (m * 37)) << QPointF(510 + (m * 20), 89 + (m * 37));//顺时针取点
        painter.setPen(pen);
        painter.setBrush(bruch);
        painter.drawPolygon(polygon, Qt::WindingFill);

        m++;
    }
}
