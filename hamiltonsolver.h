#ifndef HAMILTONSOLVER_H
#define HAMILTONSOLVER_H

#include <QString>
#include <QVector>

#include "basesolver.h"
#include "pathsolver.h"
#include "direc.h"

class TableCellH
{
public:
    TableCellH()
    {
        this->reset();
    }

    QString toString()
    {
        return QString("{ idx: %1  direc: %1 }")
                .arg(this->idx).arg(this->direc);
    }

    void reset()
    {
        this->idx = -1; // None
        this->direc = DirecType::NONE;
    }

    int idx;
    DirecType direc;
};

class HamiltonSolver: public BaseSolver
{
public:
    HamiltonSolver(Snake &snake);
    DirecType next_direc();
    void build_cycle();

    PathSolver path_solver;
    QVector<QVector<TableCellH>> table;
};

#endif // HAMILTONSOLVER_H
