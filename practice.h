#ifndef PRACTICE_H
#define PRACTICE_H

#include <QWidget>

namespace Ui {
class Practice;
}

class Practice : public QWidget
{
    Q_OBJECT

public:
    explicit Practice(QWidget *parent = nullptr);
    ~Practice();
    Ui::Practice *ui;
};

#endif // PRACTICE_H
