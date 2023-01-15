#ifndef CELLSTATE_H
#define CELLSTATE_H
#include <QObject>
namespace CellState {

Q_NAMESPACE
enum State{
  Empty,
  Zero,
  Cross
  };
 Q_ENUM_NS(State)

}

#endif // CELLSTATE_H
