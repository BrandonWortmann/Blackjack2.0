/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for counting                    *
 *                                              *
 ************************************************/

#ifndef COUNTING_H
#define COUNTING_H

#include <QWidget>

namespace Ui {
class Counting;
}

class Counting : public QWidget
{
    Q_OBJECT

public:
    explicit Counting(QWidget *parent = nullptr);
    ~Counting();
    Ui::Counting *ui;
};

#endif // COUNTING_H
