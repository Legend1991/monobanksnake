#include "maprecognizertest.h"
#include "maprecognizer.h"
#include "pos.h"
#include "direc.h"
#include "point.h"
#include "customsolver.h"

#include <QTest>

const QString pathToIamge = QString(
            "/Users/igorgoremykin/projects/build-hellkitty-Desktop_Qt_5_12_0_clang_64bit-Release/monobanksnake/screenshots/%1.png");

MapRecognizerTest::MapRecognizerTest()
{

}

void MapRecognizerTest::movingWithObstaclesCenter()
{
    this->setUp(DirecType::DOWN,
                {{9, 8}, {8, 8}, {8, 9}, {7, 9}},
                {PointType::HEAD_D, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER});

    solver->currentFlagIndex = 7;

    map->create_obstacle({11, 7});

    compareAfterMove(DirecType::LEFT, 7, 9);
    compareAfterMove(DirecType::LEFT, 6, 9);
    compareAfterMove(DirecType::LEFT, 5, 9);
    compareAfterMove(DirecType::DOWN, 5, 10);
    compareAfterMove(DirecType::DOWN, 5, 11);
    compareAfterMove(DirecType::RIGHT, 6, 11);
    compareAfterMove(DirecType::UP, 6, 10);
    compareAfterMove(DirecType::RIGHT, 7, 10);
    compareAfterMove(DirecType::RIGHT, 8, 10);
    compareAfterMove(DirecType::DOWN, 8, 11);
    compareAfterMove(DirecType::RIGHT, 9, 11);
    compareAfterMove(DirecType::UP, 9, 10);
    compareAfterMove(DirecType::RIGHT, 10, 10);
//    qDebug() << "new_direc 0:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::RIGHT, 11, 10);
    compareAfterMove(DirecType::UP, 11, 9);
    compareAfterMove(DirecType::LEFT, 10, 9);
    compareAfterMove(DirecType::UP, 10, 8);
    compareAfterMove(DirecType::RIGHT, 11, 8);
    compareAfterMove(DirecType::UP, 11, 7);
    compareAfterMove(DirecType::LEFT, 10, 7);
    compareAfterMove(DirecType::UP, 10, 6);
    compareAfterMove(DirecType::UP, 10, 5);
    compareAfterMove(DirecType::LEFT, 9, 5);
//    qDebug() << "new_direc 1:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
}

//void MapRecognizerTest::obstacleRecognition()
//{
//    QImage img(pathToIamge.arg(10), "PNG");
//    MapRecognizer recognizer = MapRecognizer(img);
//    recognizer.recognize();
//    QCOMPARE(recognizer.obstacle.y, 7);
//    QCOMPARE(recognizer.obstacle.x, 2);
//}

//void MapRecognizerTest::obstacleRecognition2()
//{
//    QImage img(pathToIamge.arg(11), "PNG");
//    MapRecognizer recognizer = MapRecognizer(img);
//    recognizer.recognize();
//    QCOMPARE(recognizer.obstacle.y, 6);
//    QCOMPARE(recognizer.obstacle.x, 2);
//}

void MapRecognizerTest::movingWithObstaclesCenterLeft()
{
    this->setUp(DirecType::RIGHT,
                {{9, 8}, {8, 8}, {8, 9}, {7, 9}},
                {PointType::HEAD_D, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER});

    solver->currentFlagIndex = 7;

    map->create_obstacle({10, 5});

    compareAfterMove(DirecType::RIGHT, 9, 9);
    compareAfterMove(DirecType::DOWN, 9, 10);
    compareAfterMove(DirecType::LEFT, 8, 10);
    compareAfterMove(DirecType::LEFT, 7, 10);
    compareAfterMove(DirecType::DOWN, 7, 11);
    compareAfterMove(DirecType::RIGHT, 8, 11);
    compareAfterMove(DirecType::RIGHT, 9, 11);
    compareAfterMove(DirecType::RIGHT, 10, 11);
    compareAfterMove(DirecType::RIGHT, 11, 11);
    compareAfterMove(DirecType::UP, 11, 10);
    compareAfterMove(DirecType::LEFT, 10, 10);
}

void MapRecognizerTest::movingWithObstaclesCenterLeft2()
{
    this->setUp(DirecType::RIGHT,
                {{8, 8}, {8, 7}, {7, 7}, {7, 6}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 6;

    compareAfterMove(DirecType::RIGHT, 9, 8);
    compareAfterMove(DirecType::DOWN, 9, 9);
    compareAfterMove(DirecType::DOWN, 9, 10);
    compareAfterMove(DirecType::LEFT, 8, 10);
    compareAfterMove(DirecType::UP, 8, 9);
    compareAfterMove(DirecType::LEFT, 7, 9);
    compareAfterMove(DirecType::DOWN, 7, 10);
    compareAfterMove(DirecType::LEFT, 6, 10);
    compareAfterMove(DirecType::UP, 6, 9);
    compareAfterMove(DirecType::LEFT, 5, 9);
    qDebug() << "new_direc 0:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::DOWN, 5, 10);
    qDebug() << "new_direc 1:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::DOWN, 5, 11);
    compareAfterMove(DirecType::RIGHT, 6, 11);
}

void MapRecognizerTest::movingWithObstaclesTopLeft()
{
    this->setUp(DirecType::LEFT,
                {{1, 2}, {1, 3}, {2, 3}, {2, 4}},
                {PointType::HEAD_L, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 0;

    map->create_obstacle({4, 1});

//    qDebug() << "new_direc 0:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::LEFT, 1, 1);
    compareAfterMove(DirecType::DOWN, 1, 2);
    compareAfterMove(DirecType::RIGHT, 2, 2);
    compareAfterMove(DirecType::DOWN, 2, 3);
    compareAfterMove(DirecType::DOWN, 2, 4);
    compareAfterMove(DirecType::RIGHT, 3, 4);
    compareAfterMove(DirecType::UP, 3, 3);
    //    qDebug() << "new_direc 1:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
}

void MapRecognizerTest::movingWithObstaclesCenterRight()
{
    this->setUp(DirecType::RIGHT,
                {{7, 8}, {7, 7}, {8, 7}, {8, 6}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 6;

    map->create_obstacle({10, 9});

    compareAfterMove(DirecType::RIGHT, 9, 7);
    compareAfterMove(DirecType::DOWN, 9, 8);
    compareAfterMove(DirecType::LEFT, 8, 8);
    compareAfterMove(DirecType::DOWN, 8, 9);
    compareAfterMove(DirecType::DOWN, 8, 10);
    compareAfterMove(DirecType::LEFT, 7, 10);
    compareAfterMove(DirecType::UP, 7, 9);
    compareAfterMove(DirecType::LEFT, 6, 9);
    compareAfterMove(DirecType::DOWN, 6, 10);
}

void MapRecognizerTest::movingWithObstaclesCenterRight2()
{
    this->setUp(DirecType::RIGHT,
                {{7, 8}, {7, 7}, {8, 7}, {8, 6}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 6;

    map->create_obstacle({9, 9});

    compareAfterMove(DirecType::RIGHT, 9, 7);
    compareAfterMove(DirecType::DOWN, 9, 8);
    compareAfterMove(DirecType::LEFT, 8, 8);
    compareAfterMove(DirecType::DOWN, 8, 9);
    compareAfterMove(DirecType::DOWN, 8, 10);
//    qDebug() << "new_direc 0:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::LEFT, 7, 10);
//    qDebug() << "new_direc 1:" << Direc::toString(next_direc) << snake->head().y << snake->head().x << solver->currentFlagIndex;
    compareAfterMove(DirecType::UP, 7, 9);
    compareAfterMove(DirecType::LEFT, 6, 9);
    compareAfterMove(DirecType::DOWN, 6, 10);
}

void MapRecognizerTest::movingWithObstaclesTopRight3()
{
    this->setUp(DirecType::DOWN,
                {{3, 10}, {3, 9}, {4, 9}, {4, 8}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 2;

    map->create_obstacle({4, 13});

    compareAfterMove(DirecType::DOWN, 10, 4);
    compareAfterMove(DirecType::RIGHT, 11, 4);
    compareAfterMove(DirecType::UP, 11, 3);
    compareAfterMove(DirecType::RIGHT, 12, 3);
    compareAfterMove(DirecType::DOWN, 12, 4);
    compareAfterMove(DirecType::DOWN, 12, 5);
    compareAfterMove(DirecType::RIGHT, 13, 5);
    compareAfterMove(DirecType::DOWN, 13, 6);
    compareAfterMove(DirecType::LEFT, 12, 6);
    compareAfterMove(DirecType::DOWN, 12, 7);
    compareAfterMove(DirecType::RIGHT, 13, 7);
}

void MapRecognizerTest::movingWithObstaclesTopRight2()
{
    this->setUp(DirecType::DOWN,
                {{3, 10}, {3, 9}, {4, 9}, {4, 8}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 2;

    map->create_obstacle({3, 12});

    compareAfterMove(DirecType::DOWN, 10, 4);
    compareAfterMove(DirecType::RIGHT, 11, 4);
    compareAfterMove(DirecType::RIGHT, 12, 4);
    compareAfterMove(DirecType::RIGHT, 13, 4);
    compareAfterMove(DirecType::DOWN, 13, 5);
    compareAfterMove(DirecType::LEFT, 12, 5);
    compareAfterMove(DirecType::DOWN, 12, 6);
    compareAfterMove(DirecType::RIGHT, 13, 6);
    compareAfterMove(DirecType::DOWN, 13, 7);
    compareAfterMove(DirecType::LEFT, 12, 7);
}

void MapRecognizerTest::movingWithObstaclesTopRight1()
{
    this->setUp(DirecType::DOWN,
                {{3, 10}, {3, 9}, {4, 9}, {4, 8}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 2;

    map->create_obstacle({4, 12});

    compareAfterMove(DirecType::DOWN, 10, 4);
    compareAfterMove(DirecType::RIGHT, 11, 4);
    compareAfterMove(DirecType::UP, 11, 3);
    compareAfterMove(DirecType::RIGHT, 12, 3);
    compareAfterMove(DirecType::RIGHT, 13, 3);
    compareAfterMove(DirecType::DOWN, 13, 4);
    compareAfterMove(DirecType::DOWN, 13, 5);
    compareAfterMove(DirecType::LEFT, 12, 5);
    compareAfterMove(DirecType::DOWN, 12, 6);
    compareAfterMove(DirecType::RIGHT, 13, 6);
    compareAfterMove(DirecType::DOWN, 13, 7);
    compareAfterMove(DirecType::LEFT, 12, 7);
}

void MapRecognizerTest::movingWithObstaclesTopRight()
{
    this->setUp(DirecType::DOWN,
                {{3, 10}, {3, 9}, {4, 9}, {4, 8}},
                {PointType::HEAD_R, PointType::BODY_HOR, PointType::BODY_HOR, PointType::BODY_HOR});

    solver->currentFlagIndex = 2;

    map->create_obstacle({3, 13});

    compareAfterMove(DirecType::DOWN, 10, 4);
    compareAfterMove(DirecType::RIGHT, 11, 4);
    compareAfterMove(DirecType::UP, 11, 3);
    compareAfterMove(DirecType::RIGHT, 12, 3);
    compareAfterMove(DirecType::DOWN, 12, 4);
    compareAfterMove(DirecType::RIGHT, 13, 4);
    compareAfterMove(DirecType::DOWN, 13, 5);
    compareAfterMove(DirecType::LEFT, 12, 5);
    compareAfterMove(DirecType::DOWN, 12, 6);
    compareAfterMove(DirecType::RIGHT, 13, 6);
    compareAfterMove(DirecType::DOWN, 13, 7);
    compareAfterMove(DirecType::LEFT, 12, 7);
}

void MapRecognizerTest::movingWithObstaclesFromLeftBottomCorner()
{
    this->setUp(DirecType::DOWN,
                {{12, 2}, {11, 2}, {11, 1}, {10, 1}, {10, 2}},
                {PointType::HEAD_D, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER});

    solver->currentFlagIndex = solver->track.size() - 3;

    map->create_obstacle({14, 2});

    compareAfterMove(DirecType::LEFT, 1, 12);
    compareAfterMove(DirecType::DOWN, 1, 13);
    compareAfterMove(DirecType::DOWN, 1, 14);
    compareAfterMove(DirecType::DOWN, 1, 15);
    compareAfterMove(DirecType::RIGHT, 2, 15);
    compareAfterMove(DirecType::RIGHT, 3, 15);
    compareAfterMove(DirecType::UP, 3, 14);

    this->clean();
}

void MapRecognizerTest::movingWithObstaclesFromLeftBottomCorner1()
{
    this->setUp(DirecType::DOWN,
                {{12, 2}, {11, 2}, {11, 1}, {10, 1}, {10, 2}},
                {PointType::HEAD_D, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER, PointType::BODY_VER});

    solver->currentFlagIndex = solver->track.size() - 3;

    map->create_obstacle({14, 3});

    compareAfterMove(DirecType::LEFT, 1, 12);
    compareAfterMove(DirecType::DOWN, 1, 13);
    compareAfterMove(DirecType::RIGHT, 2, 13);
    compareAfterMove(DirecType::DOWN, 2, 14);
    compareAfterMove(DirecType::DOWN, 2, 15);
    compareAfterMove(DirecType::RIGHT, 3, 15);
    compareAfterMove(DirecType::RIGHT, 4, 15);
    compareAfterMove(DirecType::UP, 4, 14);
    compareAfterMove(DirecType::RIGHT, 5, 14);
}

void MapRecognizerTest::movingWithObstaclesFromBottomRightCorner3()
{
    this->setUp(DirecType::UP, {{15, 14}, {15, 13}, {14, 13}, {14, 12}});

    map->create_obstacle({14, 15});

    compareAfterMove(DirecType::UP, 14, 14);
    compareAfterMove(DirecType::UP, 14, 13);
    compareAfterMove(DirecType::RIGHT, 15, 13);
    compareAfterMove(DirecType::UP, 15, 12);
    compareAfterMove(DirecType::LEFT, 14, 12);
    compareAfterMove(DirecType::UP, 14, 11);
    compareAfterMove(DirecType::RIGHT, 15, 11);

    this->clean();
}

void MapRecognizerTest::movingWithObstaclesFromBottomRightCorner()
{
    this->setUp(DirecType::UP, {{15, 14}, {15, 13}, {14, 13}, {14, 12}});

    map->create_obstacle({15, 15});

    compareAfterMove(DirecType::UP, 14, 14);
    compareAfterMove(DirecType::RIGHT, 15, 14);
    compareAfterMove(DirecType::UP, 15, 13);
    compareAfterMove(DirecType::LEFT, 14, 13);

    compareAfterMove(DirecType::UP, 14, 12);
    compareAfterMove(DirecType::RIGHT, 15, 12);
    compareAfterMove(DirecType::UP, 15, 11);
    compareAfterMove(DirecType::LEFT, 14, 11);

    this->clean();
}

void MapRecognizerTest::movingWithObstaclesFromBottomRightCorner2()
{
    this->setUp(DirecType::UP, {{15, 14}, {15, 13}, {14, 13}, {14, 12}});

    map->create_obstacle({14, 14});

    compareAfterMove(DirecType::RIGHT, 15, 15);
    compareAfterMove(DirecType::UP, 15, 14);
    compareAfterMove(DirecType::UP, 15, 13);
    compareAfterMove(DirecType::LEFT, 14, 13);

    compareAfterMove(DirecType::UP, 14, 12);
    compareAfterMove(DirecType::RIGHT, 15, 12);
    compareAfterMove(DirecType::UP, 15, 11);
    compareAfterMove(DirecType::LEFT, 14, 11);

    this->clean();
}

void MapRecognizerTest::simpleMovingFromBottomRightCorner()
{
    this->setUp(DirecType::UP, {{15, 14}, {15, 13}, {15, 12}, {15, 11}});

    map->create_food({3, 15});
    map->create_food({1, 6});

    // Track from 14,15 to 15,2

    /*
     * 4  |_
     *  ...
     * 13  _|
     * 14 |_
     * 15  _|
     */
    for (int i = 15; i > 3; i -= 2)
    {
        compareAfterMove(DirecType::RIGHT, 15, i);
        compareAfterMove(DirecType::UP, 15, i - 1);
        compareAfterMove(DirecType::LEFT, 14, i - 1);
        compareAfterMove(DirecType::UP, 14, i - 2);
    }

    compareAfterMove(DirecType::RIGHT, 15, 3);
    compareAfterMove(DirecType::UP, 15, 2);

    // Track from 15,2 to 2,1
    for (int i = 15; i > 3; i -= 2)
    {
        compareAfterMove(DirecType::UP, i, 1);
        compareAfterMove(DirecType::LEFT, i - 1, 1);
        compareAfterMove(DirecType::DOWN, i - 1, 2);
        compareAfterMove(DirecType::LEFT, i - 2, 2);
    }

    compareAfterMove(DirecType::UP, 3, 1);
    compareAfterMove(DirecType::LEFT, 2, 1);

    // Track from 2,1 to 3,1
    compareAfterMove(DirecType::LEFT, 1, 1);
    compareAfterMove(DirecType::DOWN, 1, 2);
    compareAfterMove(DirecType::RIGHT, 2, 2);
    compareAfterMove(DirecType::DOWN, 2, 3);
    compareAfterMove(DirecType::LEFT, 1, 3);

    // Track from 1,3 to 12,3
    compareAfterMove(DirecType::DOWN, 1, 4);
    compareAfterMove(DirecType::RIGHT, 2, 4);
    compareAfterMove(DirecType::RIGHT, 3, 4);
    compareAfterMove(DirecType::UP, 3, 3);
    compareAfterMove(DirecType::RIGHT, 4, 3);

    for (int i = 4; i <= 10; i += 2)
    {
        compareAfterMove(DirecType::DOWN, i, 4);
        compareAfterMove(DirecType::RIGHT, i + 1, 4);
        compareAfterMove(DirecType::UP, i + 1, 3);
        compareAfterMove(DirecType::RIGHT, i + 2, 3);
    }

    compareHead(12, 3);

    // Track from 12,3 to 13,12
    for (int i = 3; i <= 9; i += 2)
    {
        compareAfterMove(DirecType::RIGHT, 13, i);
        compareAfterMove(DirecType::DOWN, 13, i + 1);
        compareAfterMove(DirecType::LEFT, 12, i + 1);
        compareAfterMove(DirecType::DOWN, 12, i + 2);
    }

    compareAfterMove(DirecType::RIGHT, 13, 11);
    compareAfterMove(DirecType::DOWN, 13, 12);

    // Track from 13,12 to 4,13
    for (int i = 13; i > 5; i -= 2)
    {
        compareAfterMove(DirecType::DOWN, i, 13);
        compareAfterMove(DirecType::LEFT, i - 1, 13);
        compareAfterMove(DirecType::UP, i - 1, 12);
        compareAfterMove(DirecType::LEFT, i - 2, 12);
    }

    compareAfterMove(DirecType::DOWN, 5, 13);
    compareAfterMove(DirecType::LEFT, 4, 13);

    // Track from 4,13 to 3,8
    compareAfterMove(DirecType::LEFT, 3, 13);
    compareAfterMove(DirecType::UP, 3, 12);
    compareAfterMove(DirecType::RIGHT, 4, 12);
    compareAfterMove(DirecType::UP, 4, 11);

    compareAfterMove(DirecType::LEFT, 3, 11);
    compareAfterMove(DirecType::UP, 3, 10);
    compareAfterMove(DirecType::RIGHT, 4, 10);
    compareAfterMove(DirecType::UP, 4, 9);

    compareAfterMove(DirecType::LEFT, 3, 9);
    compareAfterMove(DirecType::UP, 3, 8);

    // Track from 3,8 to 8,7
    compareAfterMove(DirecType::UP, 3, 7);
    compareAfterMove(DirecType::RIGHT, 4, 7);
    compareAfterMove(DirecType::DOWN, 4, 8);
    compareAfterMove(DirecType::RIGHT, 5, 8);

    compareAfterMove(DirecType::UP, 5, 7);
    compareAfterMove(DirecType::RIGHT, 6, 7);
    compareAfterMove(DirecType::DOWN, 6, 8);
    compareAfterMove(DirecType::RIGHT, 7, 8);

    compareAfterMove(DirecType::UP, 7, 7);
    compareAfterMove(DirecType::RIGHT, 8, 7);

    // Track from 8,7 to 9,9
    compareAfterMove(DirecType::RIGHT, 9, 7);
    compareAfterMove(DirecType::DOWN, 9, 8);
    compareAfterMove(DirecType::LEFT, 8, 8);
    compareAfterMove(DirecType::DOWN, 8, 9);

    compareAfterMove(DirecType::RIGHT, 9, 9);

    // Track from 9,9 to 5,10
    compareAfterMove(DirecType::DOWN, 9, 10);
    compareAfterMove(DirecType::LEFT, 8, 10);
    compareAfterMove(DirecType::LEFT, 7, 10);
    compareAfterMove(DirecType::UP, 7, 9);
    compareAfterMove(DirecType::LEFT, 6, 9);
    compareAfterMove(DirecType::DOWN, 6, 10);
    compareAfterMove(DirecType::LEFT, 5, 10);

    // Track from 5,10 to 10,11
    compareAfterMove(DirecType::DOWN, 5, 11);
    compareAfterMove(DirecType::RIGHT, 6, 11);
    compareAfterMove(DirecType::RIGHT, 7, 11);
    compareAfterMove(DirecType::RIGHT, 8, 11);
    compareAfterMove(DirecType::RIGHT, 9, 11);
    compareAfterMove(DirecType::RIGHT, 10, 11);

    // Track from 10,11 to 11,6
    compareAfterMove(DirecType::RIGHT, 11, 11);
    compareAfterMove(DirecType::UP, 11, 10);
    compareAfterMove(DirecType::LEFT, 10, 10);
    compareAfterMove(DirecType::UP, 10, 9);

    compareAfterMove(DirecType::RIGHT, 11, 9);
    compareAfterMove(DirecType::UP, 11, 8);
    compareAfterMove(DirecType::LEFT, 10, 8);
    compareAfterMove(DirecType::UP, 10, 7);

    compareAfterMove(DirecType::RIGHT, 11, 7);
    compareAfterMove(DirecType::UP, 11, 6);

    // Track from 11,6 to 2,5
    for (int i = 11; i > 3; i -= 2)
    {
        compareAfterMove(DirecType::UP, i, 5);
        compareAfterMove(DirecType::LEFT, i - 1, 5);
        compareAfterMove(DirecType::DOWN, i - 1, 6);
        compareAfterMove(DirecType::LEFT, i - 2, 6);
    }

    compareAfterMove(DirecType::UP, 3, 5);
    compareAfterMove(DirecType::LEFT, 2, 5);

    // Track from 2,5 to 1,14
    for (int i = 5; i <= 12; i += 2)
    {
        compareAfterMove(DirecType::LEFT, 1, i);
        compareAfterMove(DirecType::DOWN, 1, i + 1);
        compareAfterMove(DirecType::RIGHT, 2, i + 1);
        compareAfterMove(DirecType::DOWN, 2, i + 2);
    }

    compareAfterMove(DirecType::LEFT, 1, 13);
    compareAfterMove(DirecType::DOWN, 1, 14);

    // Track from 1,14 to 14,15
    for (int i = 1; i <= 12; i += 2)
    {
        compareAfterMove(DirecType::DOWN, i, 15);
        compareAfterMove(DirecType::RIGHT, i + 1, 15);
        compareAfterMove(DirecType::UP, i + 1, 14);
        compareAfterMove(DirecType::RIGHT, i + 2, 14);
    }

    compareAfterMove(DirecType::DOWN, 13, 15);
    compareAfterMove(DirecType::RIGHT, 14, 15);

    // Track from 14,15 to 15,2
    for (int i = 15; i > 3; i -= 2)
    {
        compareAfterMove(DirecType::RIGHT, 15, i);
        compareAfterMove(DirecType::UP, 15, i - 1);
        compareAfterMove(DirecType::LEFT, 14, i - 1);
        compareAfterMove(DirecType::UP, 14, i - 2);
    }

    compareAfterMove(DirecType::RIGHT, 15, 3);
    compareAfterMove(DirecType::UP, 15, 2);

    this->clean();
}

void MapRecognizerTest::setUp(DirecType init_direc, QList<Pos> init_bodies, QList<PointType> init_types)
{
    map = new Map(17, 17);
    // bodies "Pos(9,12)" "Pos(9,11)" "Pos(9,10)" "Pos(9,9)"
    snake = new Snake(*map, init_direc,
                        init_bodies,
                        init_types);
    solver = new CustomSolver(*snake);
    solver->currentFlagIndex = solver->track.size() - 1;
}

void MapRecognizerTest::clean()
{
    delete solver;
    delete snake;
    delete map;
}

void MapRecognizerTest::move()
{
    next_direc = solver->next_direc();
    snake->direc_next = next_direc;
    snake->move();
}

void MapRecognizerTest::compareHead(int headX, int headY)
{
    QCOMPARE(snake->head().y, headX);    // head().y is X coordinate
    QCOMPARE(snake->head().x, headY);    // head().x is Y coordinate
}

void MapRecognizerTest::compareAfterMove(DirecType targetDirec, int headX, int headY)
{
    move();
    QCOMPARE(next_direc, targetDirec);
    QCOMPARE(snake->dead, false);
    compareHead(headX, headY);
}
