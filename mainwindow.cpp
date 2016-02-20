#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene_1 = new QGraphicsScene(this);
    scene_2 = new QGraphicsScene(this);
    scene_3 = new QGraphicsScene(this);
    scene_4 = new QGraphicsScene(this);
    scene_5 = new QGraphicsScene(this);

    f = new Frame();
    d1 = new Door(0);
    d2 = new Door(0);
    d3 = new Door(0);
    d4 = new Door(0);
    d5 = new Door(1);


    scene->addItem(f);
    scene_1->addItem(d1);
    scene_2->addItem(d2);
    scene_3->addItem(d3);
    scene_4->addItem(d4);
    scene_5->addItem(d5);


    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_3->setScene(scene);
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_4->setScene(scene);
    ui->graphicsView_4->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_5->setScene(scene);
    ui->graphicsView_5->setRenderHint(QPainter::Antialiasing);


    ui->graphicsView_6->setScene(scene_1);
    ui->graphicsView_6->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_7->setScene(scene_2);
    ui->graphicsView_7->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_8->setScene(scene_3);
    ui->graphicsView_8->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_9->setScene(scene_4);
    ui->graphicsView_9->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_10->setScene(scene_5);
    ui->graphicsView_10->setRenderHint(QPainter::Antialiasing);



    ui->lcdNumber->setDigitCount(1);
       //设置数字字体：Outline,轮廓突出，颜色为背景色；Filled，内部填充型，颜色为黑色；Flat,平面型
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
       //调色板
    QPalette lcdpat = ui->lcdNumber->palette();
       /*设置颜色，整体背景颜色 颜色蓝色,此函数的第一个参数可以设置多种。如文本、按钮按钮文字、多种*/
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
       //设置当前窗口的调色板
    ui->lcdNumber->setPalette(lcdpat);
       //设置背景色
    ui->lcdNumber->setStyleSheet("background-color: black");
    attrdlg = new AttrDlg;

    // 乘客指针数组
    p = new Passenger*[MAX_PEOPLE_NUM];
    // 电梯
    elevator = new Elevator();
    // 虚拟时钟应该在哪里声明
    v_time = new VTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartSimul_clicked()
{
    v_time.start();   // 虚拟时间开始流逝
}

void MainWindow::on_Settings_clicked()
{
    attrdlg->exec();
}
