#include "computerlogic.h"
#include <algorithm>

long long ComputerLogic::bestTurn(GameField&field, Player&zeroPlayer,
              Player&crossPlayer,Player&currentPlayer, const int centralIndex)
{

    std::vector<GameField::Cell>&field_container = field.getGameField();
    bool isEmpty = true;

    for (int pos = 0; pos < (int)field_container.size(); ++pos)
      {
          GameField::Cell& c = field_container[pos];
          bool currentNotEmpty = (c.cellState != CellState::Empty);
          isEmpty &= !currentNotEmpty;
      }

    if (isEmpty == true)
    {
        return centralIndex;
    }
    std::pair<long long, int> best_position = {0, 0};
        for (int pos = 0; pos < (int)field_container.size(); ++pos)
        {

            long long cur_weight = getCellWeight(field, zeroPlayer, crossPlayer, currentPlayer, pos);
            best_position = (cur_weight >= best_position.first) ? std::make_pair(cur_weight, pos) : best_position;
        }

    int index = best_position.second;
    return index;
}

long long ComputerLogic::getCellWeight(GameField& field, Player& zeroPlayer,
                                       Player& crossPlayer,Player&currentPlayer, int pos)
{
        std::vector<GameField::Cell>& field_container = field.getGameField();
    if (field_container[pos].cellState != CellState::Empty)
    {
        return 0;
    }
    std::vector<std::pair<int,int>>directions = {
        {1 , 0},
        {0 , 1},
        {1 , 1},
        {1 ,-1}
    };
     std::vector<std::tuple<long long, long long, long long>> weights = {
      {0, 0, 0},
      {10, 5, 1},
      {100, 10, 1},
      {1000, 100, 10},
      {10000, 1000, 10},
      {100000, 10000, 10},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100},
      {1000000, 100000, 100}
     };
     long long result_weight = 0;
     std::pair<int,int>position = field.getPosition(pos);
     std::vector<Player*>players = {&crossPlayer, &zeroPlayer};
     for (auto player : players)
     {

         bool isCurPlayer = (&currentPlayer == player);
         for (auto dv : directions)
         {
             int blocked = 0;
             int len = 1;
             for (int sgn : {-1 ,1})
             {
                 int dx = sgn*dv.first;
                 int dy = sgn*dv.second;
                 std::pair<int,int>current_position = {position.first + dx, position.second + dy};
                 int cur_len = 1;
                 while(field.isValidPosition(current_position) && cur_len++ <= 5 &&
                       field_container[field.getPosition(current_position)].cellState != CellState::Empty)
                 {
                     if (field_container[field.getPosition(current_position)].cellColor != player->color())
                     {
                        ++blocked;
                         break;
                     }
                     ++len;
                     current_position.first +=dx;
                     current_position.second+=dy;
                 }
             }
             if (isCurPlayer && len >= 4 && blocked == 0)
             {
                 result_weight += (long long)100000000;
             }
             if (!isCurPlayer && len >= 5)
             {
                 result_weight += (long long)10000000000000;
             }
             if (!isCurPlayer && len >= 4 && blocked == 0)
             {
                 result_weight += (long long)100000000000;
             }
             if (isCurPlayer && len >= 5)
             {
                 result_weight += (long long)10000000000000000;
             }
             if(blocked == 0)result_weight += std::get<0>(weights[len]);
             if(blocked == 1)result_weight += std::get<1>(weights[len]);
             if(blocked == 2)result_weight += std::get<2>(weights[len]);
         }        
     }

     return result_weight;
}
