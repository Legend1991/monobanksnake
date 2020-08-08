#include "snake.h"
#include "direc.h"

#include <stdlib.h>
#include <time.h>

#include <QDebug>

Snake::Snake(Map &game_map, DirecType init_direc, QList<Pos> init_bodies, QList<PointType> init_types): map(game_map)
{
    srand(time(NULL));
    this->init_direc = init_direc;
    this->init_bodies = init_bodies;
    this->init_types = init_types;
//    qDebug() << "Snake::constructor -> init_direc:" << Direc::toString(init_direc);
//    qDebug() << "Snake::constructor -> init_bodies:" << init_bodies;
//    qDebug() << "Snake::constructor -> init_types:" << init_types;
    this->reset(false);
}

void Snake::reset(bool reset_map)
{
    bool rand_init = false;
    if (this->init_direc == DirecType::NONE)
    {
        rand_init = true;
        short head_row = 2 + rand() % ((this->map.num_rows - 2) - 2 + 1);
        short head_col = 2 + rand() % ((this->map.num_cols - 2) - 2 + 1);
        Pos head = Pos(head_row, head_col);

        this->init_direc = DirecType(rand() % 4 + 1);
        this->init_bodies = {head, head.adj(Direc::opposite(this->init_direc))};
        this->init_types = QList<PointType>();

        if (this->init_direc == DirecType::LEFT)
            this->init_types.append(PointType::HEAD_L);
        else if (this->init_direc == DirecType::UP)
            this->init_types.append(PointType::HEAD_U);
        else if (this->init_direc == DirecType::RIGHT)
            this->init_types.append(PointType::HEAD_R);
        else if (this->init_direc == DirecType::DOWN)
            this->init_types.append(PointType::HEAD_D);

        if (this->init_direc == DirecType::LEFT || this->init_direc == DirecType::RIGHT)
            this->init_types.append(PointType::BODY_HOR);
        else if (this->init_direc == DirecType::UP || this->init_direc == DirecType::DOWN)
            this->init_types.append(PointType::BODY_VER);
    }
    this->steps = 0;
    this->dead = false;
    this->direc = this->init_direc;
    this->direc_next = DirecType::NONE;
    this->bodies = QList<Pos>(this->init_bodies);
    this->types = QList<PointType>(this->init_types);

    if (reset_map)
        this->map.reset();

    for (int i = 0; i < this->bodies.size(); ++i)
    {
        this->map.point(this->bodies[i]).type = this->types[i];
    }

    if (rand_init)
    {
        this->init_direc = DirecType::NONE;
        this->init_bodies = {};
        this->init_types = {};
    }
}

SnakeCopy Snake::copy()
{
    Map *m_copy = this->map.copy();
//    qDebug() << "Snake::copy" << m_copy->content.size();
    QList<Pos> b_copy;
    for (Pos p : this->bodies)
        b_copy << p;

    QList<PointType> pt_copy;
    for (PointType pt : this->types)
        pt_copy << pt;
    Snake s_copy = Snake(*m_copy, this->direc, b_copy, pt_copy);
//    Snake s_copy = Snake(m_copy, this->init_direc, this->init_bodies, this->init_types);
    s_copy.steps = this->steps;
    s_copy.dead = this->dead;
    s_copy.direc = this->direc;
    s_copy.direc_next = this->direc_next;
    s_copy.bodies = b_copy;
    s_copy.types = pt_copy;

    return {m_copy: *m_copy, s_copy};
}

int Snake::len()
{
    return this->bodies.size();
}

Pos Snake::head()
{
    if (this->bodies.size() <= 0)
        return Pos(-1, -1); // None
    return this->bodies[0];
}

Pos Snake::tail()
{
    if (this->bodies.size() <= 0)
        return Pos(-1, -1); // None
    return this->bodies[this->bodies.size() - 1];
}

void Snake::move_path(QList<DirecType> path)
{
    for (DirecType p : path)
        this->move(p);
}

void Snake::move(DirecType new_direc)
{
    this->eatingMoove = false;
    if (new_direc != DirecType::NONE)
        this->direc_next = new_direc;

//    qDebug() << "Snake::move" << Direc::toString(new_direc)
//             << this->dead
//             << (this->direc_next == DirecType::NONE)
//             << this->map.is_full()
//             << (this->direc_next == Direc::opposite(this->direc));

    if (this->dead
            || this->direc_next == DirecType::NONE
            || this->map.is_full()
            || this->direc_next == Direc::opposite(this->direc))
    {
                return;
    }

    NewTypes newTypes = this->new_types();
    PointType old_head_type = newTypes.old_head_type;
    PointType new_head_type = newTypes.new_head_type;
    this->map.point(this->head()).type = old_head_type;
    Pos new_head = this->head().adj(this->direc_next);
    this->bodies.prepend(new_head);
    this->types.prepend(new_head_type);

    if (!this->map.is_safe(new_head))
        this->dead = true;
    if (this->map.point(new_head).type == PointType::FOOD)
    {
        this->map.rm_food();
//        qDebug() << "Cell is food" << new_head.toString() << (this->map.point(new_head).type == PointType::FOOD);
        this->eatingMoove = true;
    }
    else
        this->rm_tail();

//    qDebug() << "Snake::move new_head:" << new_head << Direc::toString(new_direc) << this->map.is_safe(new_head) << PointCust::toString(this->map.point(new_head).type);

    this->map.point(new_head).type = new_head_type;
    this->direc = this->direc_next;
    this->steps += 1;
}

void Snake::rm_tail()
{
//    qDebug() << "Snake::rm_tail 0:" << this->tail() << PointCust::toString(this->map.point(this->tail()).type);
    this->map.point(this->tail()).type = PointType::EMPTY;
//    qDebug() << "Snake::rm_tail 1:" << this->tail() << PointCust::toString(this->map.point(this->tail()).type);
    this->bodies.removeLast();
    this->types.removeLast();
}

NewTypes Snake::new_types()
{
    PointType old_head_type;
    PointType new_head_type;

    if (this->direc_next == DirecType::LEFT)
        new_head_type = PointType::HEAD_L;
    else if (this->direc_next == DirecType::UP)
        new_head_type = PointType::HEAD_U;
    else if (this->direc_next == DirecType::RIGHT)
        new_head_type = PointType::HEAD_R;
    else if (this->direc_next == DirecType::DOWN)
        new_head_type = PointType::HEAD_D;

    if ((this->direc == DirecType::LEFT && this->direc_next == DirecType::LEFT) ||
            (this->direc == DirecType::RIGHT && this->direc_next == DirecType::RIGHT))
        old_head_type = PointType::BODY_HOR;
    else if ((this->direc == DirecType::UP && this->direc_next == DirecType::UP) ||
             (this->direc == DirecType::DOWN && this->direc_next == DirecType::DOWN))
        old_head_type = PointType::BODY_VER;
    else if ((this->direc == DirecType::RIGHT && this->direc_next == DirecType::UP) ||
             (this->direc == DirecType::DOWN && this->direc_next == DirecType::LEFT))
        old_head_type = PointType::BODY_LU;
    else if ((this->direc == DirecType::LEFT && this->direc_next == DirecType::UP) ||
             (this->direc == DirecType::DOWN && this->direc_next == DirecType::RIGHT))
        old_head_type = PointType::BODY_UR;
    else if ((this->direc == DirecType::LEFT && this->direc_next == DirecType::DOWN) ||
             (this->direc == DirecType::UP && this->direc_next == DirecType::RIGHT))
        old_head_type = PointType::BODY_RD;
    else if ((this->direc == DirecType::RIGHT && this->direc_next == DirecType::DOWN) ||
             (this->direc == DirecType::UP && this->direc_next == DirecType::LEFT))
        old_head_type = PointType::BODY_DL;

    return {old_head_type, new_head_type};
}
