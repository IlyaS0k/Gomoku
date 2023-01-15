#ifndef GAME_H
#define GAME_H


#include <QObject>
#include <string>
#include <player.h>
#include <gamefield.h>
#include "computerlogic.h"

class Game : public QObject
{
      Q_OBJECT

      Q_PROPERTY(bool isAgainstComputer READ isAgainstComputer WRITE setIsAgainstComputer NOTIFY changeIsAgainstComputer)

      Q_PROPERTY(bool isComputerTurn READ isComputerTurn WRITE setIsComputerTurn NOTIFY changeIsComputerTurn)

public:
    static const bool isAgainstComputerDefaultValue {true};
    static const bool isComputerTurnDefaultValue {true};
    explicit Game(QObject* parent = nullptr,
                  bool isAgainstComputerValue = isAgainstComputerDefaultValue,
                  bool isComputerTurnValue = isComputerTurnDefaultValue);
    bool isAgainstComputer();
    void setIsAgainstComputer(bool flag);
    bool isComputerTurn();
    void setIsComputerTurn(bool flag);
    int getCellWeight(std::vector<GameField::Cell>&gameField, int pos);
    bool checkTurn();
    Q_INVOKABLE QVariant getCurrentPlayerInsertedState();
    Q_INVOKABLE void bestTurn(const int centralIndex);
    Q_INVOKABLE QString getCurrentPlayerColor();
    Q_INVOKABLE bool nextTurn(bool isValid);
    Q_INVOKABLE void setGameField(GameField* field);
    Q_INVOKABLE void newGame();
    Q_INVOKABLE QString getVictoryString();
signals:
    void changeIsAgainstComputer();
    void changeIsComputerTurn();
private:
    bool m_againstComputer;
    bool m_isComputerTurn;
    Player m_crossPlayer;
    Player m_zeroPlayer;
    GameField* m_gameField;
    ComputerLogic m_logic;
    Player* m_currentPlayer;
};

#endif // GAME_H
