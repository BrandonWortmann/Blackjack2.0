#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "title.h"
#include "mainmenu.h"
#include "rules.h"
#include "strats.h"
#include "counting.h"
#include "practice.h"

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
    Practice* practice;

    void hideAll();

public slots:
    void startBtnPressed();
    void rulesBtnPressed();
    void stratsBtnPressed();
    void countingBtnPressed();
    void practiceBtnPressed();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
