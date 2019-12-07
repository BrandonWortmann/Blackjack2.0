#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for mainwindow                  *
 *                                              *
 ************************************************/

#include <QMainWindow>
#include "title.h"
#include "mainmenu.h"
#include "rules.h"
#include "counting.h"
#include "gameui.h"
#include "tutorial.h"
#include "countingtutorial.h"
#include "intro.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Title* title;
    MainMenu* menu;
    Rules* rules;
    Counting* counting;
    GameUI* gameUI;
    TutorialUI* tutorial;
    CountingTutorial* countTutorial;
    Intro* intro;

    void hideAll();

public slots:
    void startBtnPressed();
    void introBtnPressed();
    void rulesBtnPressed();
    void stratsBtnPressed();
    void countingBtnPressed();
    void practiceBtnPressed();
    void toCardsPage();
    void toChipsPage();
    void toTutorialPage();
    void toCountTutorialPage();
    void backTutorialPage();
    void backCountTutorialPage();
    void backRulesPage();
    void backCardsPage();
    void countPopup();

    void updateCard1(int);
    void updateCard2(int);
    void updateCard3(int);
    void updateCard4(int);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
