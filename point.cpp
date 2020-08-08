#include "point.h"

PointCust::PointCust()
{

}

QString PointCust::toString(PointType point)
{
    if (point == PointType::EMPTY)
        return "EMPTY";
    else if (point == PointType::WALL)
        return "WALL";
    else if (point == PointType::FOOD)
        return "FOOD";
    else if (point == PointType::HEAD_L)
        return "HEAD_L";
    else if (point == PointType::HEAD_U)
        return "HEAD_U";
    else if (point == PointType::HEAD_R)
        return "HEAD_R";
    else if (point == PointType::HEAD_D)
        return "HEAD_D";
    else if (point == PointType::BODY_LU)
        return "BODY_LU";
    else if (point == PointType::BODY_UR)
        return "BODY_UR";
    else if (point == PointType::BODY_RD)
        return "BODY_RD";
    else if (point == PointType::BODY_DL)
        return "BODY_DL";
    else if (point == PointType::BODY_HOR)
        return "BODY_HOR";
    else if (point == PointType::BODY_VER)
        return "BODY_VER";
    else
        return "NONE";
}
