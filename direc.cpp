#include "direc.h"

Direc::Direc()
{

}

DirecType Direc::opposite(DirecType direc)
{
    if (direc == DirecType::LEFT)
        return DirecType::RIGHT;
    else if (direc == DirecType::RIGHT)
        return DirecType::LEFT;
    else if (direc == DirecType::UP)
        return DirecType::DOWN;
    else if (direc == DirecType::DOWN)
        return DirecType::UP;
    else
        return DirecType::NONE;
}

QString Direc::toString(DirecType direc)
{
    if (direc == DirecType::LEFT)
        return "LEFT";
    else if (direc == DirecType::RIGHT)
        return "RIGHT";
    else if (direc == DirecType::UP)
        return "UP";
    else if (direc == DirecType::DOWN)
        return "DOWN";
    else
        return "NONE";
}
