#ifndef INTRO_H
#define INTRO_H

#include <QWidget>

namespace Ui {
class Intro;
}

class Intro : public QWidget
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = nullptr);
    ~Intro();
    Ui::Intro *ui;
};

#endif // INTRO_H
