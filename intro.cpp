/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  intro.cpp                                   *
 *  Introduction widget that explains app       *
 *  structure.                                  *
 *                                              *
 ************************************************/

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
