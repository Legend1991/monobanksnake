#include "pos.h"

Pos::Pos(): x(0), y(0)
{

}

Pos::Pos(short x, short y)
{
    this->x = x;
    this->y = y;
}

QString Pos::toString()
{
    return QString("Pos(%1,%2)").arg(this->x).arg(this->y);
}

bool Pos::operator ==(const Pos &other) const
{
    return this->x == other.x
            && this->y == other.y;
}

bool Pos::operator !=(const Pos &other) const
{
    return !(*this == other);
}

Pos Pos::operator -() const
{
    return Pos(-this->x, -this->y);
}

Pos Pos::operator +(const Pos &other) const
{
    return Pos(this->x + other.x, this->y + other.y);
}

Pos Pos::operator -(const Pos &other) const
{
    return *this + (-other);
}

uint qHash(const Pos &pos)
{
    return (uint(pos.x) << 16) | uint(pos.y);
}

int Pos::manhattan_dist(const Pos &p1, const Pos &p2)
{
    return qAbs(p1.x - p2.x) + qAbs(p1.y - p2.y);
}

DirecType Pos::direc_to(const Pos &adj_pos)
{
    if (this->x == adj_pos.x) {
        int diff = this->y - adj_pos.y;
        if (diff == 1)
            return DirecType::LEFT;
        else if (diff == -1)
            return DirecType::RIGHT;
    } else if (this->y == adj_pos.y) {
        int diff = this->x - adj_pos.x;
        if (diff == 1)
            return DirecType::UP;
        else if (diff == -1)
            return DirecType::DOWN;
    }
    return DirecType::NONE;
}

Pos Pos::adj(DirecType direc)
{
    if (direc == DirecType::LEFT)
        return Pos(this->x, this->y - 1);
    else if (direc == DirecType::RIGHT)
        return Pos(this->x, this->y + 1);
    else if (direc == DirecType::UP)
        return Pos(this->x - 1, this->y);
    else if (direc == DirecType::DOWN)
        return Pos(this->x + 1, this->y);
    else
        return *this + Pos(); // None
}

QList<Pos> Pos::all_adj()
{
    QList<Pos> adjs;
    for (DirecType direc : DIREC_TYPES) {
        if (direc != DirecType::NONE)
            adjs << this->adj(direc);
    }
    return adjs;
}

QDebug operator<<(QDebug debug, const Pos &pos)
{
    debug << "Pos(" << pos.x << "," << pos.y << ")";
    return debug;
}
