#ifndef MAPRECOGNIZERTEST_H
#define MAPRECOGNIZERTEST_H

#include <QObject>

#include "pos.h"
#include "map.h"
#include "snake.h"
#include "customsolver.h"

class MapRecognizerTest : public QObject
{
    Q_OBJECT
public:
    MapRecognizerTest();
    void setUp(DirecType init_direc, QList<Pos> init_bodies, QList<PointType> init_types = {
            PointType::HEAD_R,
            PointType::BODY_HOR,
            PointType::BODY_HOR,
            PointType::BODY_HOR
        });
    void clean();
    void move();
    void compareHead(int headX, int headY);
    void compareAfterMove(DirecType targetDirec, int headX, int headY);

    DirecType next_direc;
    Map *map;
    Snake *snake;
    CustomSolver *solver;

private slots:
    void simpleMovingFromBottomRightCorner();
    void movingWithObstaclesFromBottomRightCorner();
    void movingWithObstaclesFromBottomRightCorner2();
    void movingWithObstaclesFromBottomRightCorner3();
    void movingWithObstaclesFromLeftBottomCorner();
    void movingWithObstaclesFromLeftBottomCorner1();
    void movingWithObstaclesTopRight();
    void movingWithObstaclesTopRight1();
    void movingWithObstaclesTopRight2();
    void movingWithObstaclesTopRight3();
    void movingWithObstaclesCenterRight();
    void movingWithObstaclesCenterRight2();
    void movingWithObstaclesCenterLeft();
    void movingWithObstaclesCenterLeft2();
    void movingWithObstaclesTopLeft();
    void movingWithObstaclesCenter();
//    void obstacleRecognition();
//    void obstacleRecognition2();
};

#endif // MAPRECOGNIZERTEST_H
