#ifndef POS_H
#define POS_H

#include <QString>
#include <QList>
#include <QDebug>

#include "direc.h"

class Pos
{
public:
    Pos();
    Pos(short x, short y);
    QString toString();
    static int manhattan_dist(const Pos &p1, const Pos &p2);
    DirecType direc_to(const Pos &adj_pos);
    Pos adj(DirecType direc);
    QList<Pos> all_adj();

    bool operator ==(const Pos &other) const;
    bool operator !=(const Pos &other) const;
    Pos operator -() const;
    Pos operator +(const Pos &other) const;
    Pos operator -(const Pos &other) const;

    short x;
    short y;
};

uint qHash(const Pos &pos);
QDebug operator<<(QDebug, const Pos &);

#endif // POS_H
