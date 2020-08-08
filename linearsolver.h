#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H

#include "snake.h"
#include "direc.h"
#include "map.h"
#include "pos.h"

class LinearSolver
{
public:
    LinearSolver(Snake &snake);
    DirecType next_direc();

    Snake &snake;
    Map &map;
};

#endif // LINEARSOLVER_H
