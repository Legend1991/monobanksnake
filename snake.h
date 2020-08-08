#ifndef SNAKE_H
#define SNAKE_H

#include <QList>

#include "map.h"
#include "point.h"
#include "pos.h"

struct SnakeCopy;
struct NewTypes;

class Snake
{
public:
    Snake(Map &game_map, DirecType init_direc, QList<Pos> init_bodies, QList<PointType> init_types);
    void reset(bool reset_map = true);
    SnakeCopy copy();
    int len();
    Pos head();
    Pos tail();
    void move_path(QList<DirecType> path);
    void move(DirecType new_direc = DirecType::NONE);
    void rm_tail();
    NewTypes new_types();

    Map &map;
    DirecType init_direc;
    QList<Pos> init_bodies;
    QList<PointType> init_types;
    int steps;
    bool dead;
    DirecType direc;
    DirecType direc_next;
    QList<Pos> bodies;
    QList<PointType> types;
    bool eatingMoove;
};

struct SnakeCopy
{
    Map m_copy;
    Snake s_copy;
};

struct NewTypes
{
    PointType old_head_type;
    PointType new_head_type;
};

#endif // SNAKE_H
