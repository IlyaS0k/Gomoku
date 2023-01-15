#include "player.h"
#include "qvariant.h"
Player::Player(){}
Player::Player(QString color, CellState::State insertedState) :
m_color{color},
m_insertedState{insertedState}
{

}

QString Player::color()
{
    return m_color;
}

QVariant Player::insertedState()
{
    return QVariant(m_insertedState);
}

void Player::setColor(QString color)
{
    m_color = color;
}
