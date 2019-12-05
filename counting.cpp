/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  counting.cpp                                *
 *  Counting popup cheatsheet widget.           *
 *                                              *
 ************************************************/

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
