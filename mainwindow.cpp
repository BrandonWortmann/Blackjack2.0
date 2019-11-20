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

    QStackedWidget* stack = new QStackedWidget;
    stack->addWidget(title);
    stack->addWidget(menu);
    stack->addWidget(rules);
    stack->addWidget(counting);
    stack->addWidget(strats);
    stack->addWidget(practice);
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
    this->practice->show();
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
    QPoint coord = title->ui->label->pos();
    QSize dim = title->ui->label->size();
    title->ui->label->setGeometry(coord.x() , height, dim.width(), dim.height());
}

