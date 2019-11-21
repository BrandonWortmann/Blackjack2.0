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

public slots:
    void startAnimation();

signals:
    void updateTextHeight(int);
};

#endif // TITLE_H
