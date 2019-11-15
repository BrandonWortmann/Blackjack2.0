#include "title.h"
#include "ui_title.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);
}

Title::~Title()
{
    delete ui;
}
