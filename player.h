#ifndef PLAYER_H
#define PLAYER_H

#include <QColor>
#include <QObject>
#include "CellState.h"

class Player
{

public:
    inline static const QString computerDefaultPlayerColor {"red"};
    Player();
    Player(QString color, CellState::State insertedState);
    QString color();
    QVariant insertedState();
    void setColor(QString color);
private:
    QString m_color;
    CellState::State m_insertedState;
};
#endif // PLAYER_H
