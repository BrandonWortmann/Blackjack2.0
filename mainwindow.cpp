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
#include "gameui.h"
#include "ui_gameui.h"
#include "tutorial.h"
#include "ui_tutorial.h"
#include "countingtutorial.h"
#include "ui_countingtutorial.h"
#include <QStackedWidget>
#include "intro.h"
#include "ui_intro.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * Used to display all of our blackjack game
 * user interface elements
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting up all our sections
    title = new Title;
    menu = new MainMenu;
    rules = new Rules;
    intro = new Intro;
    tutorial = new TutorialUI;
    countTutorial = new CountingTutorial;
    gameUI = new GameUI;

    // Stack widget used to display different UI
    QStackedWidget* stack = new QStackedWidget;  
    stack->addWidget(title);
    stack->addWidget(menu);
    stack->addWidget(rules);
    stack->addWidget(gameUI);
    stack->addWidget(intro);
    stack->addWidget(countTutorial);
    stack->addWidget(tutorial);
    this->setCentralWidget(stack);

    // Establishing connections
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
    connect(countTutorial->ui->returnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(tutorial->ui->returnBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);
    connect(countTutorial->ui->returnButton, &QPushButton::pressed, this, &MainWindow::backCountTutorialPage);
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

/**
 * @brief MainWindow::~MainWindow
 * Mainwindow destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete menu;
    delete title;
    delete rules;
    delete gameUI;
}

/**
 * @brief MainWindow::startBtnPressed
 * Start button slot
 */
void MainWindow::startBtnPressed(){
    hideAll();
    this->menu->show();
}

/**
 * @brief MainWindow::introBtnPressed
 * Introduction button slot
 */
void MainWindow::introBtnPressed(){
    hideAll();
    this->intro->show();
}

/**
 * @brief MainWindow::rulesBtnPressed
 * Rules button slot
 */
void MainWindow::rulesBtnPressed(){
    hideAll();
    this->rules->show();
    rules->ui->innerStack->setCurrentIndex(0);
}

/**
 * @brief MainWindow::stratsBtnPressed
 * Strategies button slot
 */
void MainWindow::stratsBtnPressed(){
    hideAll();
    tutorial->ui->tutorialStack->setCurrentIndex(0);
    this->tutorial->show();
}

/**
 * @brief MainWindow::countingBtnPressed
 * Counting button slot
 */
void MainWindow::countingBtnPressed(){
    hideAll();
    this->countTutorial->show();
}

/**
 * @brief MainWindow::practiceBtnPressed
 * Practice button slot
 */
void MainWindow::practiceBtnPressed(){
    hideAll();
    this->gameUI->show();
}

/**
 * @brief MainWindow::hideAll
 * Hides all stack widgets
 */
void MainWindow::hideAll(){
    this->title->hide();
    this->rules->hide();
    this->menu->hide();
    this->gameUI->hide();
    this->tutorial->hide();
    this->intro->hide();
    this->countTutorial->hide();
}

/**
 * @brief MainWindow::toCardsPage
 * Slot that takes the user to the cards page
 */
void MainWindow::toCardsPage()
{
    rules->ui->rulesPage->hide();
    rules->ui->cardsPage->show();
}

/**
 * @brief MainWindow::toChipsPage
 * Slot that takes the user to the chips page
 */
void MainWindow::toChipsPage()
{
    rules->ui->cardsPage->hide();
    rules->ui->chipsPage->show();
}

/**
 * @brief MainWindow::toTutorialPage
 * Slot that takes the user to the tutorial page
 */
void MainWindow::toTutorialPage()
{
    tutorial->ui->infoPage->hide();
    tutorial->ui->gamePage->show();
}

/**
 * @brief MainWindow::toCountTutorialPage
 * Slot that takes the user to the count tutorial page
 */
void MainWindow::toCountTutorialPage()
{
    countTutorial->ui->infoPage->hide();
    countTutorial->ui->gamePage->show();
}

/**
 * @brief MainWindow::backRulesPage
 * Returns the user to the rules page
 */
void MainWindow::backRulesPage()
{
    rules->ui->cardsPage->hide();
    rules->ui->rulesPage->show();
}

/**
 * @brief MainWindow::backTutorialPage
 * Returns the user to the tutorial page
 */
void MainWindow::backTutorialPage()
{
    tutorial->ui->gamePage->hide();
    tutorial->ui->infoPage->show();
    startBtnPressed();
}

/**
 * @brief MainWindow::backCountTutorialPage
 * Returns the user to the counting tutorial page
 */
void MainWindow::backCountTutorialPage()
{
    countTutorial->ui->gamePage->hide();
    countTutorial->ui->infoPage->show();
    startBtnPressed();
}

/**
 * @brief MainWindow::backCardsPage
 * Returns the user back to the cards page
 */
void MainWindow::backCardsPage()
{
    rules->ui->chipsPage->hide();
    rules->ui->cardsPage->show();
}

/**
 * @brief MainWindow::updateCard1
 * @param height
 * Title screen bouncing card 1
 */
void MainWindow::updateCard1(int height)
{
    QPoint coord = title->ui->bouncingCard1->pos();
    QSize dim = title->ui->bouncingCard1->size();
    title->ui->bouncingCard1->setGeometry(coord.x(), height, dim.width(), dim.height());
}

/**
 * @brief MainWindow::updateCard2
 * @param height
 * Title screen bouncing card 2
 */
void MainWindow::updateCard2(int height)
{
    QPoint coord = title->ui->bouncingCard2->pos();
    QSize dim = title->ui->bouncingCard2->size();
    title->ui->bouncingCard2->setGeometry(coord.x(), height, dim.width(), dim.height());
}

/**
 * @brief MainWindow::updateCard3
 * @param height
 * Title screen bouncing card 3
 */
void MainWindow::updateCard3(int height)
{
    QPoint coord = title->ui->bouncingCard3->pos();
    QSize dim = title->ui->bouncingCard3->size();
    title->ui->bouncingCard3->setGeometry(coord.x(), height, dim.width(), dim.height());
}

/**
 * @brief MainWindow::updateCard4
 * @param height
 * Title screen bouncing card 4
 */
void MainWindow::updateCard4(int height)
{
    QPoint coord = title->ui->bouncingCard4->pos();
    QSize dim = title->ui->bouncingCard4->size();
    title->ui->bouncingCard4->setGeometry(coord.x(), height, dim.width(), dim.height());
}
