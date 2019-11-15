#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "title.h"

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
    QWidget* menu;
    QWidget* rules;
    QWidget* strats;
    QWidget* counting;
    QWidget* practice;

public slots:
    void startBtnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
