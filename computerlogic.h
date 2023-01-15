#ifndef COMPUTERLOGIC_H
#define COMPUTERLOGIC_H

#include "gamefield.h"
#include <string>
#include <vector>
#include <set>

class ComputerLogic
{

public:
   ComputerLogic(){};
   long long getCellWeight(GameField&field,Player&zeroPlayer, Player&crossPlayer,Player&currentPlayer, int pos);
   long long bestTurn(GameField&field, Player&zeroPlayer,
                        Player&crossPlayer,Player&currentPlayer, const int centralIndex);
private:

};

#endif // COMPUTERLOGIC_H
