#include "game.h"
Game::Game(QObject* parent, bool isAgainstComputerValue,bool isComputerTurnValue):
    QObject(parent),
    m_againstComputer{isAgainstComputerValue},
    m_isComputerTurn{isComputerTurnValue},
    m_crossPlayer{Player("red", CellState::Cross)},
    m_zeroPlayer{Player("blue", CellState::Zero)},
    m_currentPlayer{&m_crossPlayer}
{

}
bool Game::checkTurn()
{
    return m_againstComputer && m_currentPlayer->color() == Player::computerDefaultPlayerColor;
}
bool Game::nextTurn(bool isValid)
{
    if(!isValid)return false;
    m_currentPlayer = &((m_currentPlayer == &m_zeroPlayer) ?
                m_crossPlayer : m_zeroPlayer);
    setIsComputerTurn(checkTurn());
    return true;
}
bool Game::isAgainstComputer()
{
    return m_againstComputer;
}
void Game::setIsAgainstComputer(bool flag)
{
    if( m_againstComputer == flag)return;
    m_againstComputer = flag;
    emit changeIsAgainstComputer();
}

QVariant Game::getCurrentPlayerInsertedState()
{
    return m_currentPlayer->insertedState();
}

QString Game::getCurrentPlayerColor()
{
    return m_currentPlayer->color();
}
void Game::setGameField(GameField* field)
{
     m_gameField = field;
}

void Game::newGame()
{
    m_gameField->resetField();
    m_currentPlayer = &m_crossPlayer;
    m_logic = ComputerLogic();
    setIsComputerTurn(checkTurn());
}
QString Game::getVictoryString()
{

    QString colStr = m_gameField->getGameField()[m_gameField->posChain()].cellColor;
    QString result = "Game over! " +
            colStr.toUpper() + " player win!";
    return result;
}
bool Game::isComputerTurn()
{
    return m_isComputerTurn;
}
void Game::setIsComputerTurn(bool flag)
{
    if(flag == m_isComputerTurn)return;

    m_isComputerTurn = flag;
    emit changeIsComputerTurn();
}

void Game::bestTurn(const int centralIndex)
{
   int index = m_logic.bestTurn(*m_gameField, m_zeroPlayer, m_crossPlayer, *m_currentPlayer, centralIndex);
   this->nextTurn(m_gameField->setState(index, m_currentPlayer->insertedState(),m_currentPlayer->color()));
}
