#include "counting.h"
#include "ui_counting.h"

Counting::Counting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Counting)
{
    ui->setupUi(this);
}

Counting::~Counting()
{
    delete ui;
}
