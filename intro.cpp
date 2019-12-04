#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);
}

Intro::~Intro()
{
    delete ui;
}
