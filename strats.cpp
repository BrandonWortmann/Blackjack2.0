#include "strats.h"
#include "ui_strats.h"

Strats::Strats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Strats)
{
    ui->setupUi(this);
}

Strats::~Strats()
{
    delete ui;
}
