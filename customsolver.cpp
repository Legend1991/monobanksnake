#include "customsolver.h"

#include <QPair>

BasePath CustomSolver::BasePathRightUp = {DirecType::RIGHT, DirecType::UP, DirecType::LEFT, DirecType::UP};
BasePath CustomSolver::BasePathUpLeft = {DirecType::UP, DirecType::LEFT, DirecType::DOWN, DirecType::LEFT};
BasePath CustomSolver::BasePathLeftDown = {DirecType::LEFT, DirecType::DOWN, DirecType::RIGHT, DirecType::DOWN};
BasePath CustomSolver::BasePathDownRight = {DirecType::DOWN, DirecType::RIGHT, DirecType::UP, DirecType::RIGHT};
BasePath CustomSolver::BasePathRightDown = {DirecType::RIGHT, DirecType::DOWN, DirecType::LEFT, DirecType::DOWN};
BasePath CustomSolver::BasePathDownLeft = {DirecType::DOWN, DirecType::LEFT, DirecType::UP, DirecType::LEFT};
BasePath CustomSolver::BasePathLeftUp = {DirecType::LEFT, DirecType::UP, DirecType::RIGHT, DirecType::UP};
BasePath CustomSolver::BasePathUpRight = {DirecType::UP, DirecType::RIGHT, DirecType::DOWN, DirecType::RIGHT};
BasePath CustomSolver::BasePathLeftRight = {DirecType::DOWN, DirecType::RIGHT, DirecType::RIGHT,
                                            DirecType::RIGHT, DirecType::RIGHT, DirecType::RIGHT};
BasePath CustomSolver::BasePathDownNone = {DirecType::LEFT, DirecType::LEFT, DirecType::LEFT, DirecType::DOWN};
BasePath CustomSolver::BasePathNoneRight = {DirecType::DOWN, DirecType::RIGHT, DirecType::UP, DirecType::RIGHT};

static QHash<QPair<DirecType, DirecType>, BasePath> direcBasePathMap = {
    {{DirecType::RIGHT, DirecType::UP}, CustomSolver::BasePathRightUp},
    {{DirecType::UP, DirecType::LEFT}, CustomSolver::BasePathUpLeft},
    {{DirecType::LEFT, DirecType::DOWN}, CustomSolver::BasePathLeftDown},
    {{DirecType::DOWN, DirecType::RIGHT}, CustomSolver::BasePathDownRight},
    {{DirecType::RIGHT, DirecType::DOWN}, CustomSolver::BasePathRightDown},
    {{DirecType::DOWN, DirecType::LEFT}, CustomSolver::BasePathDownLeft},
    {{DirecType::LEFT, DirecType::UP}, CustomSolver::BasePathLeftUp},
    {{DirecType::UP, DirecType::RIGHT}, CustomSolver::BasePathUpRight},
    {{DirecType::LEFT, DirecType::RIGHT}, CustomSolver::BasePathLeftRight},
    {{DirecType::DOWN, DirecType::NONE}, CustomSolver::BasePathDownNone},
    {{DirecType::NONE, DirecType::RIGHT}, CustomSolver::BasePathNoneRight}
};

const Track trackMain = {
    {x: 14.5, y: 1.5, direc: DirecType::LEFT},
    {x: 1.5, y: 1.5, direc: DirecType::DOWN},
    {x: 0.5, y: 3.5, direc: DirecType::RIGHT},
    {x: 12.5, y: 3.5, direc: DirecType::DOWN},
    {x: 12.5, y: 12.5, direc: DirecType::LEFT},
    {x: 3.5, y: 12.5, direc: DirecType::UP},
    {x: 3.5, y: 7.5, direc: DirecType::RIGHT},
    {x: 8.5, y: 7.5, direc: DirecType::DOWN},
    {x: 9.5, y: 9.5, direc: DirecType::LEFT},
    {x: 4.5, y: 10.5, direc: DirecType::RIGHT},
    {x: 10.5, y: 10.5, direc: DirecType::UP},
    {x: 10.5, y: 5.5, direc: DirecType::LEFT},
    {x: 1.5, y: 5.5, direc: DirecType::DOWN},
    {x: 1.5, y: 14.5, direc: DirecType::RIGHT},
    {x: 14.5, y: 14.5, direc: DirecType::UP}
};

const Track trackAlt = {
    {x: 14.5, y: 1.5, direc: DirecType::LEFT},
    {x: 1.5, y: 1.5, direc: DirecType::DOWN},
    {x: 0.5, y: 3.5, direc: DirecType::RIGHT},
    {x: 12.5, y: 3.5, direc: DirecType::DOWN},
    {x: 12.5, y: 12.5, direc: DirecType::LEFT},
    {x: 3.5, y: 12.5, direc: DirecType::UP},
    {x: 3.5, y: 7.5, direc: DirecType::RIGHT},
    {x: 8.5, y: 7.5, direc: DirecType::DOWN},
    {x: 9.5, y: 9.5, direc: DirecType::NONE},
    {x: 4.5, y: 10.5, direc: DirecType::RIGHT},
    {x: 10.5, y: 10.5, direc: DirecType::UP},
    {x: 10.5, y: 5.5, direc: DirecType::LEFT},
    {x: 1.5, y: 5.5, direc: DirecType::DOWN},
    {x: 1.5, y: 14.5, direc: DirecType::RIGHT},
    {x: 14.5, y: 14.5, direc: DirecType::UP}
};

CustomSolver::CustomSolver(Snake &snake): snake(snake), map(snake.map)
{
    this->currentDirecIndex = 0;
    this->currentFlagIndex = 0;
    this->track = trackMain;
}

DirecType CustomSolver::next_direc()
{
    Flag curr_flag = this->currFlag();
//    qDebug() << "CustomSolver::next_direc():" << curr_flag.x << curr_flag.y
//             << this->snake.head().y << this->snake.head().x
//             << this->isNextFlagRiched()
//             << this->prevFlag().x << this->prevFlag().y
//             << Direc::toString(direcBasePathMap[{this->prevFlag().direc, curr_flag.direc}][0]);
    this->basePath = direcBasePathMap[{this->prevFlag().direc, curr_flag.direc}];
    DirecType nextDirec = this->basePath[this->currentDirecIndex];

    if (snake.head() == Pos(9, 5))
    {
        return DirecType::DOWN;
    }

    if (snake.head() == Pos(9, 6) && snake.map.food == Pos(9, 5))
    {
        return DirecType::LEFT;
    }

    bool isMoveInvalid = this->isMoveInvalid(nextDirec);
//    qDebug() << "CustomSolver::next_direc" << this->snake.head().y << this->snake.head().x
//             << isMoveInvalid << Direc::toString(nextDirec);

    if (isMoveInvalid)
        return this->basePath[this->prevDirecIndex()];

    bool isDoubleMoveInvalid = this->isDoubleMoveInvalid({nextDirec, this->basePath[this->nextDirecIndex()]});
//    qDebug() << "CustomSolver::next_direc" << this->snake.head().y << this->snake.head().x
//             << isDoubleMoveInvalid << Direc::toString(nextDirec)
//             << Direc::toString(this->basePath[this->nextDirecIndex()]) << this->snake.map.obstacle;
    if (isDoubleMoveInvalid)
        return this->basePath[this->prevDirecIndex()];

    this->currentDirecIndex = this->nextDirecIndex();
    return nextDirec;
}

Flag CustomSolver::nextFlag()
{
    return this->track[this->nextFlagIndex()];
}

Flag CustomSolver::currFlag()
{
    if (this->isNextFlagRiched())
    {
        if ((snake.head() == Pos(9, 8) || snake.head() == Pos(10, 5))
                && (snake.map.obstacle == Pos(10, 7)
                    || snake.map.obstacle == Pos(10, 8)
                    || snake.map.obstacle == Pos(11, 7)
                    || snake.map.obstacle == Pos(11, 8)
                    || snake.map.obstacle == Pos(11, 9)
                    || snake.map.obstacle == Pos(11, 10)))
        {
            this->track = trackAlt;
        }
        else
        {
            this->track = trackMain;
        }

        this->currentFlagIndex = this->nextFlagIndex();
        this->currentDirecIndex = 0;
    }
    return this->track[this->currentFlagIndex];
}

Flag CustomSolver::prevFlag()
{
    return this->track[this->prevFlagIndex()];
}

int CustomSolver::nextFlagIndex()
{
    return (this->currentFlagIndex + 1) % this->track.size();
}

int CustomSolver::prevFlagIndex()
{
    if (this->currentFlagIndex == 0)
        return this->track.size() - 1;
    return this->currentFlagIndex - 1;
}

int CustomSolver::nextDirecIndex()
{
    return (this->currentDirecIndex + 1) % this->basePath.size();
}

int CustomSolver::prevDirecIndex()
{
    if (this->currentDirecIndex == 0)
        return this->basePath.size() - 1;
    return this->currentDirecIndex - 1;
}

bool CustomSolver::isMoveInvalid(DirecType direcNext)
{
    SnakeCopy snakeCopy = this->snake.copy();
    Snake s_copy = snakeCopy.s_copy;
    s_copy.move(direcNext);
    return s_copy.dead;
}

bool CustomSolver::isDoubleMoveInvalid(QList<DirecType> path)
{
    SnakeCopy snakeCopy = this->snake.copy();
    Snake s_copy = snakeCopy.s_copy;
    s_copy.move(path[0]);
    s_copy.move(path[0]);

    SnakeCopy snakeCopy2 = this->snake.copy();
    Snake s_copy2 = snakeCopy2.s_copy;
    s_copy2.move(path[0]);
    s_copy2.move(path[1]);

    bool isSideMove = this->currentDirecIndex == 0 || this->currentDirecIndex == 2;

    return (s_copy.dead || isSideMove) && s_copy2.dead;
}

bool CustomSolver::isNextFlagRiched()
{
    Flag curr_flag = this->nextFlag();

    if (snake.head() == Pos(9, 8)
            && (snake.map.obstacle == Pos(10, 7)
                || snake.map.obstacle == Pos(10, 8)
                || snake.map.obstacle == Pos(11, 7)
                || snake.map.obstacle == Pos(11, 8)
                || snake.map.obstacle == Pos(11, 9)
                || snake.map.obstacle == Pos(11, 10)))
    {
        return true;
    }

    if ((this->snake.map.obstacle == Pos(10, 9)
         || this->snake.map.obstacle == Pos(9, 9))
            && qFuzzyCompare(curr_flag.x, 9.5f)
            && qFuzzyCompare(curr_flag.y, 9.5f))
    {
        curr_flag.x = 8.5;
        curr_flag.y = 9.5;
    }

    if ((this->snake.map.obstacle == Pos(3, 1)
         || this->snake.map.obstacle == Pos(4, 1))
            && qFuzzyCompare(curr_flag.x, 0.5f)
            && qFuzzyCompare(curr_flag.y, 3.5f))
    {
        curr_flag.x = 1.5;
        curr_flag.y = 3.5;
    }

//    if (snake.head() == Pos(9, 5)
//            && qFuzzyCompare(curr_flag.x, 4.5f)
//            && qFuzzyCompare(curr_flag.y, 10.5f))
//    {
//        curr_flag.x = 4.5;
//        curr_flag.y = 9.5;
//    }

    if ((this->snake.map.obstacle == Pos(10, 5)
         || this->snake.map.obstacle == Pos(11, 5)
         || this->snake.map.obstacle == Pos(10, 6)
         || this->snake.map.obstacle == Pos(11, 6))
            && qFuzzyCompare(curr_flag.x, 4.5f)
            && qFuzzyCompare(curr_flag.y, 10.5f)
            && snake.head() != Pos(9, 5))
    {
        curr_flag.x = 6.5;
        curr_flag.y = 10.5;
    }

    return qAbs(this->snake.head().y - curr_flag.x) < 1
            && qAbs(this->snake.head().x - curr_flag.y) < 1;
}
