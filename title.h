#ifndef TITLE_H
#define TITLE_H
#include "Box2D/Box2D.h"
#include <stdio.h>

#include <QWidget>

namespace Ui {
class Title;
}

class Title : public QWidget
{
    Q_OBJECT

public:
    explicit Title(QWidget *parent = nullptr);
    ~Title();
    Ui::Title *ui;
    bool gameStart;

    b2World world;
    b2Body* body;

    b2Body* body2;
    b2Body* body3;
    b2Body* body4;

public slots:
    void startAnimation();

signals:
    void updateTextHeight(int);

    void updateCard1(int);
    void updateCard2(int);
    void updateCard3(int);
    void updateCard4(int);

};

#endif // TITLE_H
