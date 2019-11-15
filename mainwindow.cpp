#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "title.h"
#include "ui_title.h"
#include "mainmenu.h"
#include "ui_mainmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    title = new Title;
    this->layout();
    this->setCentralWidget(title);
    this->title->show();

    menu = new MainMenu;
    this->layout();

    connect(title->ui->startBtn, &QPushButton::pressed, this, &MainWindow::startBtnPressed);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete menu;
    delete title;
}

void MainWindow::startBtnPressed(){
    this->setCentralWidget(menu);
    this->menu->show();
}
