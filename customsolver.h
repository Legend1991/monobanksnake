#ifndef CUSTOMSOLVER_H
#define CUSTOMSOLVER_H

#include "snake.h"
#include "direc.h"
#include "map.h"
#include "pos.h"

typedef QList<DirecType> BasePath;

struct Flag
{
    float x;
    float y;
    DirecType direc;
};

typedef QList<Flag> Track;

class CustomSolver
{
public:
    CustomSolver(Snake &snake);
    DirecType next_direc();
    Flag nextFlag();
    Flag currFlag();
    bool isNextFlagRiched();
    int nextFlagIndex();
    int prevFlagIndex();
    Flag prevFlag();
    int nextDirecIndex();
    int prevDirecIndex();
    bool isMoveInvalid(DirecType direcNext);
    bool isDoubleMoveInvalid(QList<DirecType> path);

    static QList<DirecType> BasePathRightUp;
    static QList<DirecType> BasePathUpLeft;
    static QList<DirecType> BasePathLeftDown;
    static QList<DirecType> BasePathDownRight;
    static QList<DirecType> BasePathRightDown;
    static QList<DirecType> BasePathDownLeft;
    static QList<DirecType> BasePathLeftUp;
    static QList<DirecType> BasePathUpRight;
    static QList<DirecType> BasePathLeftRight;
    static QList<DirecType> BasePathDownNone;
    static QList<DirecType> BasePathNoneRight;

    Snake &snake;
    Map &map;
    int currentDirecIndex;
    int currentFlagIndex;
    BasePath basePath;
    Track track;
};

#endif // CUSTOMSOLVER_H
