/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for strats                      *
 *                                              *
 ************************************************/

#ifndef STRATS_H
#define STRATS_H

#include <QWidget>

namespace Ui {
class Strats;
}

class Strats : public QWidget
{
    Q_OBJECT

public:
    explicit Strats(QWidget *parent = nullptr);
    ~Strats();
    Ui::Strats *ui;
};

#endif // STRATS_H
