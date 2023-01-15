
#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QChar>
#include <qqml.h>

namespace CellNamespace
{
    Q_NAMESPACE         // required for meta object creation
    enum State {
    Empty,
    Zero,
    Cross
    };
    Q_ENUM_NS(State)
}


class Cell : public QObject
{

        Q_OBJECT

        Q_PROPERTY(QChar qstate READ qstate WRITE setQState NOTIFY qstateChanged)
        QML_ELEMENT

        Q_PROPERTY(CellNamespace::State state READ state WRITE setState NOTIFY qstateChanged)
         QML_ELEMENT

public:

    explicit Cell(QObject *parent = nullptr);
    QChar qstate();
    CellNamespace::State state();
    void setQState(const QChar &state);
    void setState(const CellNamespace::State &state);
signals:
    void qstateChanged();
private:
    QChar m_qstate;
    CellNamespace::State m_state;
};

#endif // CELL_H

