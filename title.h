#ifndef TITLE_H
#define TITLE_H

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
    void startAnimation();

signals:
    void updateTextHeight(int);
};

#endif // TITLE_H
