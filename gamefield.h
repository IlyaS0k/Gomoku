#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QString>
#include <QAbstractTableModel>
#include <vector>
#include "CellState.h"
#include "player.h"

class GameField : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int posChain READ posChain WRITE setPosChain NOTIFY changePosChain);
    Q_PROPERTY(int sideSize READ sideSize CONSTANT);
    Q_PROPERTY(int fieldSize READ fieldSize CONSTANT);
public:
   static const int defaultFieldSideSize {80};
   static const int defaultChainLength {5};
   static const int defaultPosChainValue {-1};
   enum Roles
   {
     displayColorRole = Qt::UserRole + 1
   };
   QHash<int, QByteArray> roleNames() const;
   struct Cell
   {
      QString cellColor = "white";
      CellState::State cellState = CellState::Empty;
      Cell():cellColor("white"),cellState(CellState::Empty){};
      void setValue(Player&player)
      {
          this->cellColor = player.color();
          this->cellState = player.insertedState().value<CellState::State>();
      }
   };
   std::pair<int,int>getPosition(const int index);
   int getPosition(const std::pair<int,int> index);
   bool isValidPosition(std::pair<int,int>position);
   GameField(QObject* parent = nullptr, const int fieldSize = defaultFieldSideSize,
             const int posChainValue = defaultPosChainValue);
   int rowCount(const QModelIndex &parent) const override;
   QVariant data(const QModelIndex &index, int role) const override;
   std::vector<Cell>& getGameField();
   void resetField();
   int posChain();
   int sideSize();
   int fieldSize();
   void setPosChain(const int pos);
   bool checkChain(const int index, int chainLength = defaultChainLength);
   Q_INVOKABLE bool setState(const int index, QVariant state, QString color);
   Q_INVOKABLE QColor getCellColor(int index);
signals:
   void changeHasColor();
   void changePosChain();
private:
   std::vector<Cell>m_gameField;
   int m_fieldSideSize;
   int m_fieldSize;
   int m_posChain;
};

#endif // GAMEFIELD_H
