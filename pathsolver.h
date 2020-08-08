#ifndef PATHSOLVER_H
#define PATHSOLVER_H

#include <QVector>
#include <QList>

#include <climits>

#include "basesolver.h"
#include "snake.h"
#include "pos.h"

class TableCell
{
public:
    TableCell()
    {
        this->reset();
    }

    QString toString()
    {
        return QString("{ dist: %1  parent: %2  visit: %3 }")
                .arg(this->dist).arg(this->parent.toString()).arg(visit);
    }

    void reset()
    {
        parent = Pos(-1, -1); // None
        dist = INT_MAX;
        visit = false;
    }

    Pos parent;
    int dist;
    bool visit;
};

class PathSolver: public BaseSolver
{
public:
    PathSolver(Snake &snake);
    void reset_table();
    QList<DirecType> shortest_path_to_food();
    QList<DirecType> longest_path_to_tail();
    QList<DirecType> path_to(const Pos &des, const QString &path_type);
    QList<DirecType> shortest_path_to(const Pos &des);
    QList<DirecType> longest_path_to(const Pos &des);
    QList<DirecType> build_path(const Pos &src, const Pos &des);
    bool is_valid(const Pos &pos);

    Snake &snake;
    Map &map;
    QVector<QVector<TableCell>> table;
};

#endif // PATHSOLVER_H
