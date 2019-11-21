#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "title.h"
#include "ui_title.h"
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "rules.h"
#include "ui_rules.h"
#include "counting.h"
#include "ui_counting.h"
#include "practice.h"
#include "ui_practice.h"
#include "strats.h"
#include "ui_strats.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    title = new Title;
    menu = new MainMenu;
    rules = new Rules;
    strats = new Strats;
    counting = new Counting;
    practice = new Practice;
    gameUI = new GameUI;

    QStackedWidget* stack = new QStackedWidget;
    stack->addWidget(title);
    stack->addWidget(menu);
    stack->addWidget(rules);
    stack->addWidget(counting);
    stack->addWidget(strats);
    stack->addWidget(practice);
    stack->addWidget(gameUI);
    this->setCentralWidget(stack);

    connect(title->ui->startBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);

    connect(menu->ui->rulesBtn, &QPushButton::pressed, this, &MainWindow::rulesBtnPressed);
    connect(menu->ui->stratsBtn, &QPushButton::pressed, this, &MainWindow::stratsBtnPressed);
    connect(menu->ui->countingBtn, &QPushButton::pressed, this, &MainWindow::countingBtnPressed);
    connect(menu->ui->practiceBtn, &QPushButton::pressed, this, &MainWindow::practiceBtnPressed);

    connect(counting->ui->countingReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(rules->ui->rulesReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(strats->ui->stratsReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(practice->ui->practiceReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);

    connect(title, &Title::updateTextHeight, this, &MainWindow::updateTitleText);
    connect(title, &Title::updateCard1, this, &MainWindow::updateCard1);
    connect(title, &Title::updateCard2, this, &MainWindow::updateCard2);
    connect(title, &Title::updateCard3, this, &MainWindow::updateCard3);
    connect(title, &Title::updateCard4, this, &MainWindow::updateCard4);



    title->show();
    title->startAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete menu;
    delete title;
    delete strats;
    delete rules;
    delete counting;
    delete practice;
    delete gameUI;
}

void MainWindow::startBtnPressed(){
    hideAll();
    this->menu->show();
}

void MainWindow::rulesBtnPressed(){
    hideAll();
    this->rules->show();
}

void MainWindow::stratsBtnPressed(){
    hideAll();
    this->strats->show();
}

void MainWindow::countingBtnPressed(){
    hideAll();
    this->counting->show();
}

void MainWindow::practiceBtnPressed(){
    hideAll();
    this->gameUI->show();
}

void MainWindow::hideAll(){
    this->title->hide();
    this->rules->hide();
    this->strats->hide();
    this->counting->hide();
    this->menu->hide();
    this->practice->hide();
}

void MainWindow::updateTitleText(int height)
{
//    QPoint coord1 = title->ui->label->pos();
//    QSize dim1 = title->ui->label->size();

//    QPoint coord2 = title->ui->label_3->pos();
//    QSize dim2 = title->ui->label_3->size();

//    title->ui->label->setGeometry(coord1.x() , height, dim1.width(), dim1.height());
//    title->ui->label_3->setGeometry(coord2.x() , height, dim2.width(), dim2.height());

    height = height + 220;

    QPoint coord1 = title->ui->bouncingCard1->pos();
    QPoint coord2 = title->ui->bouncingCard2->pos();
    QPoint coord3 = title->ui->bouncingCard3->pos();
    QPoint coord4 = title->ui->bouncingCard4->pos();

    QSize dim1 = title->ui->bouncingCard1->size();
    QSize dim2 = title->ui->bouncingCard2->size();
    QSize dim3 = title->ui->bouncingCard3->size();
    QSize dim4 = title->ui->bouncingCard4->size();

    title->ui->bouncingCard1->setGeometry(coord1.x(), height, dim1.width(), dim1.height());
    title->ui->bouncingCard2->setGeometry(coord2.x(), height, dim2.width(), dim2.height());
    title->ui->bouncingCard3->setGeometry(coord3.x(), height, dim3.width(), dim3.height());
    title->ui->bouncingCard4->setGeometry(coord4.x(), height, dim4.width(), dim4.height());

}

void MainWindow::updateCard1(int height)
{
    QPoint coord = title->ui->bouncingCard1->pos();
    QSize dim = title->ui->bouncingCard1->size();
    title->ui->bouncingCard1->setGeometry(coord.x(), height, dim.width(), dim.height());
}

void MainWindow::updateCard2(int height)
{
    QPoint coord = title->ui->bouncingCard2->pos();
    QSize dim = title->ui->bouncingCard2->size();
    title->ui->bouncingCard2->setGeometry(coord.x(), height, dim.width(), dim.height());
}
void MainWindow::updateCard3(int height)
{
    QPoint coord = title->ui->bouncingCard3->pos();
    QSize dim = title->ui->bouncingCard3->size();
    title->ui->bouncingCard3->setGeometry(coord.x(), height, dim.width(), dim.height());
}
void MainWindow::updateCard4(int height)
{
    QPoint coord = title->ui->bouncingCard4->pos();
    QSize dim = title->ui->bouncingCard4->size();
    title->ui->bouncingCard4->setGeometry(coord.x(), height, dim.width(), dim.height());
}
