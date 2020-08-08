#ifndef DIREC_H
#define DIREC_H

#include <QString>

enum DirecType
{
    NONE = 0,
    LEFT = 1,
    UP = 2,
    RIGHT = 3,
    DOWN = 4
};

const DirecType DIREC_TYPES[] = {DirecType::NONE, DirecType::LEFT, DirecType::UP, DirecType::RIGHT, DirecType::DOWN};
const int DIREC_TYPES_LENGTH = 5;

class Direc
{
public:
    Direc();

    static DirecType opposite(DirecType direc);
    static QString toString(DirecType direc);
};

#endif // DIREC_H
