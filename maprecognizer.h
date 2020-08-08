#ifndef MAPRECOGNIZER_H
#define MAPRECOGNIZER_H

#include <QImage>
#include <QList>

#include "pos.h"
#include "point.h"

class MapRecognizer
{
public:
    MapRecognizer(QImage img);
    void recognize();

    Pos food;
    Pos obstacle;
    QList<Pos> catBodies;
    DirecType direc;
    QList<PointType> catTypes;

private:
    bool isFood(QColor color);
    bool isCat(QColor color);
    bool isObstacle(QColor color);
    void checkCatHead(int x, int y);
    void fixCatTypes();

    QImage img;
};

#endif // MAPRECOGNIZER_H
