#ifndef MONOBANKSNAKE_H
#define MONOBANKSNAKE_H

#include <QElapsedTimer>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QHash>
#include <QProcess>
#include <QObject>
#include <QRunnable>

#include <stdio.h>
#include <stdlib.h>

#include "pos.h"

class MonobankSnake : QObject
{
    Q_OBJECT
public:
    MonobankSnake();
    void run();
    void click(int x, int y);
    void swipe(int x, int y, DirecType direc);
    void mouseMoveFromTo(int pX0, int pY0, int pX1, int pY1);
    void mouseMoveTo(int pX, int pY);
    void mousePress(int x, int y);
    void mouseRelease();

    Pos food;
    Pos obstacle;
    bool shouldRebuildCycle;

private:
    QList<Pos> reversed(const QList<Pos> & in);
    QProcess *screenshotProc;

    void onNewScreenshot();
};

class ScreenshotWorker : public QRunnable
{
public:
    explicit ScreenshotWorker();
    virtual void run();
};

#endif // MONOBANKSNAKE_H
