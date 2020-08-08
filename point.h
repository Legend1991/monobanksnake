#ifndef POINT_H
#define POINT_H

#include <QString>

enum PointType
{
    EMPTY = 0,
    WALL = 1,
    FOOD = 2,
    HEAD_L = 100,
    HEAD_U = 101,
    HEAD_R = 102,
    HEAD_D = 103,
    BODY_LU = 104,
    BODY_UR = 105,
    BODY_RD = 106,
    BODY_DL = 107,
    BODY_HOR = 108,
    BODY_VER = 109,
};

class PointCust
{
public:
    PointCust();

    PointType type = PointType::EMPTY;
    static QString toString(PointType point);
};

#endif // POINT_H
