/************************************************
 *      A9 - Educational App                    *
 *  Author: Wasted Potential                    *
 *  CS 3505                                     *
 *                                              *
 *  header file for rules                       *
 *                                              *
 ************************************************/

#ifndef RULES_H
#define RULES_H

#include <QWidget>

namespace Ui {
class Rules;
}

class Rules : public QWidget
{
    Q_OBJECT

public:
    explicit Rules(QWidget *parent = nullptr);
    ~Rules();
    Ui::Rules *ui;

};

#endif // RULES_H
