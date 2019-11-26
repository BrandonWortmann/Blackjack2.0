#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "title.h"
#include "mainmenu.h"
#include "rules.h"
#include "strats.h"
#include "counting.h"
#include "practice.h"
#include "gameui.h"

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
    Strats* strats;
    Counting* counting;
    GameUI* gameUI;

    void hideAll();

public slots:
    void startBtnPressed();
    void rulesBtnPressed();
    void stratsBtnPressed();
    void countingBtnPressed();
    void practiceBtnPressed();
    void toCardsPage();
    void toChipsPage();
    void backRulesPage();
    void backCardsPage();

    void updateTitleText(int);
    void updateCard1(int);
    void updateCard2(int);
    void updateCard3(int);
    void updateCard4(int);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
