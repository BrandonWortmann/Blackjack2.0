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
#include "strats.h"
#include "ui_strats.h"
#include "gameui.h"
#include "ui_gameui.h"
#include "tutorial.h"
#include "ui_tutorial.h"
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
    tutorial = new TutorialUI;
    gameUI = new GameUI;

    QStackedWidget* stack = new QStackedWidget;  
    stack->addWidget(title);
    stack->addWidget(menu);
    stack->addWidget(rules);
    stack->addWidget(gameUI);
    stack->addWidget(tutorial);
    this->setCentralWidget(stack);

    connect(title->ui->startBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);

    connect(menu->ui->rulesBtn, &QPushButton::pressed, this, &MainWindow::rulesBtnPressed);
    connect(menu->ui->stratsBtn, &QPushButton::pressed, this, &MainWindow::stratsBtnPressed);
    connect(menu->ui->countingBtn, &QPushButton::pressed, this, &MainWindow::countingBtnPressed);
    connect(menu->ui->practiceBtn, &QPushButton::pressed, this, &MainWindow::practiceBtnPressed);

    connect(rules->ui->rulesReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(gameUI->ui->gameUIReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(tutorial->ui->tutorialUIReturnBtn, &QPushButton::pressed, this, &MainWindow::backTutorialPage);

    connect(rules->ui->rulesReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(tutorial->ui->tutorialNextBtn, &QPushButton::pressed, this, &MainWindow::toTutorialPage);
    connect(rules->ui->toRulesBtn, &QPushButton::pressed, this, &MainWindow::toRulesPage);
    connect(rules->ui->toCardsBtn, &QPushButton::pressed, this, &MainWindow::toCardsPage);
    connect(rules->ui->toChipsBtn, &QPushButton::pressed, this, &MainWindow::toChipsPage);
    connect(rules->ui->backIntroBtn, &QPushButton::pressed, this, &MainWindow::backIntroPage);
    connect(rules->ui->backCardsBtn, &QPushButton::pressed, this, &MainWindow::backCardsPage);
    connect(rules->ui->backRulesBtn, &QPushButton::pressed, this, &MainWindow::backRulesPage);


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
    delete gameUI;
}

void MainWindow::startBtnPressed(){
    hideAll();
    this->menu->show();
}

void MainWindow::rulesBtnPressed(){
    hideAll();
    this->rules->show();
    rules->ui->innerStack->setCurrentIndex(0);
}

void MainWindow::stratsBtnPressed(){
    hideAll();
    tutorial->ui->tutorialStack->setCurrentIndex(0);
    this->tutorial->show();
}

void MainWindow::countingBtnPressed(){
    hideAll();
    this->gameUI->show();
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
    this->gameUI->hide();
    this->tutorial->hide();
}

void MainWindow::updateTitleText(int height)
{
//    QPoint coord1 = title->ui->label->pos();
//    QSize dim1 = title->ui->label->size();

//    QPoint coord2 = title->ui->label_3->pos();
//    QSize dim2 = title->ui->label_3->size();

//    title->ui->label->setGeometry(coord1.x() , height, dim1.width(), dim1.height());
//    title->ui->label_3->setGeometry(coord2.x() , height, dim2.width(), dim2.height());

}

void MainWindow::toRulesPage()
{
    rules->ui->introPage->hide();
    rules->ui->rulesPage->show();
}

void MainWindow::toCardsPage()
{
    rules->ui->rulesPage->hide();
    rules->ui->cardsPage->show();
}

void MainWindow::toChipsPage()
{
    rules->ui->cardsPage->hide();
    rules->ui->chipsPage->show();
}


void MainWindow::toTutorialPage()
{
    tutorial->ui->infoPage->hide();
    tutorial->ui->gamePage->show();
}

void MainWindow::backRulesPage()
{
    rules->ui->cardsPage->hide();
    rules->ui->rulesPage->show();
}

void MainWindow::backTutorialPage()
{
    tutorial->ui->gamePage->hide();
    tutorial->ui->infoPage->show();
    startBtnPressed();
}


void MainWindow::backCardsPage()
{
    rules->ui->chipsPage->hide();
    rules->ui->cardsPage->show();
}

void MainWindow::backIntroPage(){
    rules->ui->rulesPage->hide();
    rules->ui->introPage->show();
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
