#ifndef MAP_H
#define MAP_H

#include <QVector>

#include "point.h"
#include "pos.h"

class Map
{
public:
    Map(int num_rows, int num_cols);
    void reset();
    Map *copy();
    PointCust &point(const Pos &pos);
    bool is_inside(const Pos &pos);
    bool is_empty(const Pos &pos);
    bool is_safe(const Pos &pos);
    bool is_full();
    bool has_food();
    bool has_obstacle();
    void rm_food();
    void rm_obstacle();
    Pos &create_food(const Pos &pos);
    void create_rand_food();
    Pos &create_obstacle(const Pos &pos);
    void create_rand_obstacle();

    int num_rows;
    int num_cols;
    int capacity;
    QVector<QVector<PointCust>> content;
    Pos food;
    Pos obstacle;
};

#endif // MAP_H
