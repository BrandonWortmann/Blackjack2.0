/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  strats.cpp                                  *
 *  Widget that holds Hit/Stay popup            *
 *  cheatsheet.                                 *
 *                                              *
 ************************************************/

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
