#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <vector>
#include <QLabel>

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
    void doubleDown();
    void split();
    void checkDealer();
    void dealCard(bool);


private:
    Ui::GameUI *ui;
    int money;
    int userNum;
    int wager;
    int playerNextCardPos;
    int dealerNextCardPos;
    QVector<QLabel*> cards;
    int index;
};

#endif // GAMEUI_H
