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
