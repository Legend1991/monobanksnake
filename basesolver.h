#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "map.h"
#include "snake.h"
#include "direc.h"

class BaseSolver
{
public:
    BaseSolver(Snake &snake);
//    virtual ~BaseSolver();
//    void setSnake(Snake &snake);
//    virtual DirecType next_direc() = 0;

    Snake &snake;
    Map map;
};

#endif // BASESOLVER_H
