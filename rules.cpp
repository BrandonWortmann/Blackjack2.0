/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  rules.cpp                                   *
 *  Widget that holds info page that describes  *
 *  rules of the game, and card/chip values.    *
 *                                              *
 ************************************************/

#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
}

Rules::~Rules()
{
    delete ui;
}
