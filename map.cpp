#include "map.h"

#include <QDebug>

#include <stdlib.h>
#include <time.h>

Map::Map(int num_rows, int num_cols)
{
    srand(time(NULL));
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->capacity = (num_rows - 2) * (num_cols - 2);
    this->content = QVector<QVector<PointCust>>(num_rows);
    for (int i = 0; i < num_rows; ++i)
        this->content[i] = QVector<PointCust>(num_cols, PointCust());
}

void Map::reset()
{
    this->food = Pos(-1, -1);

    for (int i = 0; i < this->num_rows; ++i)
    {
        for (int j = 0; j < this->num_cols; ++j)
        {
            if (i == 0 || i == this->num_rows - 1
                    || j == 0 || j == this->num_cols - 1)
            {
                this->content[i][j].type = PointType::WALL;
            }
            else
            {
                this->content[i][j].type = PointType::EMPTY;
            }
        }
    }
}

Map *Map::copy()
{
    Map *copy = new Map(this->num_rows, this->num_cols);
//    qDebug() << "Map::copy:" << this->num_rows << this->num_cols;
    for (int i = 0; i < this->num_rows; ++i)
    {
        for (int j = 0; j < this->num_cols; ++j)
        {
            copy->content[i][j].type = this->content[i][j].type;
        }
    }
    copy->obstacle = this->obstacle;
    return copy;
}

PointCust &Map::point(const Pos &pos)
{
    return this->content[pos.x][pos.y];
}

bool Map::is_inside(const Pos &pos)
{
    return pos.x > 0 && pos.x < this->num_rows - 1
            && pos.y > 0 && pos.y < this->num_cols - 1;
}

bool Map::is_empty(const Pos &pos)
{
    return this->is_inside(pos) && this->point(pos).type == PointType::EMPTY;
}

bool Map::is_safe(const Pos &pos)
{
    return this->is_inside(pos)
            && (this->point(pos).type == PointType::EMPTY
                || this->point(pos).type == PointType::FOOD);
}

bool Map::is_full()
{
    for (int i = 1; i < this->num_rows - 1; ++i)
    {
        for (int j = 1; j < this->num_cols - 1; ++j)
        {
            PointType t = this->content[i][j].type;
            if (t < PointType::HEAD_L)
                return false;
        }
    }
    return true;
}

bool Map::has_food()
{
    return this->food.x != -1 && this->food.y != -1;
}

bool Map::has_obstacle()
{
    return this->obstacle.x != -1 && this->obstacle.y != -1;
}

void Map::rm_food()
{
    if (this->has_food())
    {
        this->point(this->food).type = PointType::EMPTY;
        this->food = Pos(-1, -1);
    }
}

void Map::rm_obstacle()
{
    if (this->has_obstacle())
    {
        this->point(this->obstacle).type = PointType::EMPTY;
        this->obstacle = Pos(-1, -1);
    }
}

Pos &Map::create_food(const Pos &pos)
{
    this->point(pos).type = PointType::FOOD;
    this->food = pos;
//    qDebug() << "Map::create_food:" << pos.x << pos.y;
    return this->food;
}

void Map::create_rand_food()
{
    QList<Pos> empty_pos;
    for (short i = 1; i < this->num_rows - 1; ++i)
    {
        for (short j = 1; j < this->num_cols - 1; ++j)
        {
            PointType t = this->content[i][j].type;
            if (t == PointType::EMPTY)
                empty_pos << Pos(i, j);
            else if (t == PointType::FOOD)
                return; // None
        }
    }
    if (empty_pos.size())
        this->create_food(empty_pos[rand() % empty_pos.size()]);
}

Pos &Map::create_obstacle(const Pos &pos)
{
    this->point(pos).type = PointType::WALL;
    this->obstacle = pos;
//    qDebug() << "Map::create_obstacle:" << pos.x << pos.y;
    return this->obstacle;
}

void Map::create_rand_obstacle()
{
    QList<Pos> empty_pos;
    for (short i = 1; i < this->num_rows - 1; ++i)
    {
        for (short j = 1; j < this->num_cols - 1; ++j)
        {
            PointType t = this->content[i][j].type;
            if (t == PointType::EMPTY)
                empty_pos << Pos(i, j);
        }
    }
    this->create_obstacle(empty_pos[rand() % empty_pos.size()]);
}
