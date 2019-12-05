/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  mainwindow.cpp                              *
 *  Underlying QMainWindow that holds all       *
 *  widgets and windows that are displayed.     *
 *                                              *
 ************************************************/

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
#include "counttutorial.h"
#include "ui_counttutorial.h"
#include <QStackedWidget>
#include "intro.h"
#include "ui_intro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    title = new Title;
    menu = new MainMenu;
    rules = new Rules;
    strats = new Strats;
    intro = new Intro;
    counting = new Counting;
    tutorial = new TutorialUI;
    countTutorial = new CountTutorial;
    gameUI = new GameUI;

    QStackedWidget* stack = new QStackedWidget;  
    stack->addWidget(title);
    stack->addWidget(menu);
    stack->addWidget(rules);
    stack->addWidget(gameUI);
    stack->addWidget(intro);
    stack->addWidget(countTutorial);
    stack->addWidget(tutorial);
    this->setCentralWidget(stack);

    connect(title->ui->startBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);

    connect(menu->ui->introBtn, &QPushButton::pressed, this, &MainWindow::introBtnPressed);
    connect(menu->ui->rulesBtn, &QPushButton::pressed, this, &MainWindow::rulesBtnPressed);
    connect(menu->ui->stratsBtn, &QPushButton::pressed, this, &MainWindow::stratsBtnPressed);
    connect(menu->ui->countingBtn, &QPushButton::pressed, this, &MainWindow::countingBtnPressed);
    connect(menu->ui->practiceBtn, &QPushButton::pressed, this, &MainWindow::practiceBtnPressed);

    connect(intro->ui->introReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(rules->ui->rulesReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(gameUI->ui->gameUIReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(tutorial->ui->tutorialUIReturnBtn, &QPushButton::pressed, this, &MainWindow::backTutorialPage);
    connect(countTutorial->ui->countTutorialUIReturnBtn, &QPushButton::pressed, this, &MainWindow::backCountTutorialPage);

    connect(rules->ui->rulesReturnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(tutorial->ui->tutorialNextBtn, &QPushButton::pressed, this, &MainWindow::toTutorialPage);
    connect(countTutorial->ui->countTutorialBtn, &QPushButton::pressed, this, &MainWindow::toCountTutorialPage);
    connect(rules->ui->toCardsBtn, &QPushButton::pressed, this, &MainWindow::toCardsPage);
    connect(rules->ui->toChipsBtn, &QPushButton::pressed, this, &MainWindow::toChipsPage);
    connect(rules->ui->backCardsBtn, &QPushButton::pressed, this, &MainWindow::backCardsPage);
    connect(rules->ui->backRulesBtn, &QPushButton::pressed, this, &MainWindow::backRulesPage);

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

void MainWindow::introBtnPressed(){
    hideAll();
    this->intro->show();
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
    this->countTutorial->show();
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
    this->intro->hide();
    this->countTutorial->hide();
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

void MainWindow::toCountTutorialPage()
{
    countTutorial->ui->infoPage->hide();
    countTutorial->ui->gamePage->show();
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

void MainWindow::backCountTutorialPage()
{
    countTutorial->ui->gamePage->hide();
    countTutorial->ui->infoPage->show();
    startBtnPressed();
}

void MainWindow::backCardsPage()
{
    rules->ui->chipsPage->hide();
    rules->ui->cardsPage->show();
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
