#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>

namespace Ui {
class GameUI;
}

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();
    void startGame();
    void beginDealing();
    void hitMe();
    void stand();
    void checkDealer();


private:
    Ui::GameUI *ui;
    int money;
    int userNum;
    int wager;
};

#endif // GAMEUI_H
