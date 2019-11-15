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

private:
    Ui::Counting *ui;
};

#endif // COUNTING_H
