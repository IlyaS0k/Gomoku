#include "gamefield.h"
#include <math.h>
GameField::GameField(QObject* parent, int fieldSize,int posChainValue) :
QAbstractListModel(parent),
m_fieldSideSize{fieldSize},
m_fieldSize{fieldSize*fieldSize},
m_posChain{posChainValue}
{
    m_gameField.resize(m_fieldSize);
}
int GameField::posChain()
{
    return m_posChain;
}
void GameField::setPosChain(const int pos)
{
    if(m_posChain == pos)
    {
        return;
    }
    m_posChain = pos;
    emit changePosChain();
}
int GameField::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   return m_fieldSize;
}
QVariant GameField::data(const QModelIndex &index, int role) const
{

    if (!index.isValid()) {
          return QVariant();
      }
    if (role == Qt::DisplayRole) {
        QChar result = ' ';
        CellState::State currentState = m_gameField[index.row()].cellState;
        if (currentState != CellState::Empty)
        {     result = currentState ==
                CellState::Zero ? 'O' : 'X';
        }
        return QVariant(result);
    }
   if (role == Roles::displayColorRole) {
     QColor result = m_gameField[index.row()].cellColor;
     return QVariant(result);
   }
    return QVariant();
}
int GameField::sideSize()
{
    return m_fieldSideSize;
}
int GameField::fieldSize()
{
    return m_fieldSize;
}
bool GameField::setState(const int index, QVariant state, QString color)
  {
    if (m_gameField[index].cellState != CellState::Empty)
    {
        return false;
    }
      m_gameField[index].cellColor = color;
      m_gameField[index].cellState = (CellState::State)(state.toInt());
      if(checkChain(index))
      {
          setPosChain(index);
      }
      emit dataChanged(createIndex(index, 0), createIndex(index, 0));
      return true;
  }
QColor GameField::getCellColor(int index)
{
    return m_gameField[index].cellColor;
}
void GameField::resetField()
{
    m_gameField.clear();
    setPosChain(defaultPosChainValue);
    m_gameField.resize(m_fieldSize);
    emit dataChanged(createIndex(0, 0), createIndex(m_fieldSize, 0));
}
std::pair<int,int>GameField::getPosition(const int index)
{
   return std::make_pair(index/m_fieldSideSize,
                         index%m_fieldSideSize);
}
int GameField::getPosition(const std::pair<int,int> index)
{
   return index.first*m_fieldSideSize +
          index.second;
}
bool GameField::isValidPosition(std::pair<int,int>position)
{
    return position.first >= 0 && position.first < m_fieldSideSize
        && position.second >= 0 && position.second < m_fieldSideSize;
}
bool GameField::checkChain(const int index, int chainLength)
{
    std::pair<int,int>position = getPosition(index);
    CellState::State state = m_gameField[index].cellState;
    if (state == CellState::Empty || m_posChain != defaultPosChainValue)
    {
        return false;
    }
    std::vector<std::pair<int,int>>directions = {
        {1 , 0},
        {0 , 1},
        {1 , 1},
        {1 ,-1}
    };
    for (auto dv : directions)
    {
        int len = 1;
        for (auto sgn : {-1 , 1})
        {
            std::pair<int,int>current_position = position;
            int dx = sgn*dv.first;
            int dy = sgn*dv.second;
          for (int i = 0;i <= chainLength; ++i)
          {
             current_position.first +=dx;
             current_position.second+=dy;
            if (!isValidPosition(current_position) ||
            m_gameField[getPosition(current_position)].cellState != state)
            {
              break;
            }
           ++len;
          }
        }
        if (len >= chainLength)
        {
            return true;
        }
    }
    return false;
}
QHash<int, QByteArray> GameField::roleNames() const
{
    auto result = QAbstractItemModel::roleNames();
    result.insert(displayColorRole, "displayColor");
    return result;
}
std::vector<GameField::Cell>& GameField::getGameField()
{
    return m_gameField;
}

