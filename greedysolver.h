#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include "snake.h"
#include "pathsolver.h"
#include "direc.h"
#include "map.h"
#include "pos.h"

#include <QList>

class GreedySolver
{
public:
    GreedySolver(Snake &snake);
    DirecType next_direc(bool manhattan);

    Snake &snake;
    Map &map;
};

#endif // GREEDYSOLVER_H
