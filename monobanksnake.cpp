#include "monobanksnake.h"

#include "map.h"
#include "snake.h"
#include "customsolver.h"
#include "hamiltonsolver.h"
#include "greedysolver.h"
#include "pathsolver.h"
#include "direc.h"
#include "pos.h"
#include "point.h"
#include "maprecognizer.h"

#include <QThreadPool>
#include <QThread>
#include <QMutex>
#include <QHash>
#include <QDateTime>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QtMac>
#include <QColor>

#include <stdlib.h>

#include <algorithm>
#include <functional>
#include <x86intrin.h>
#include <immintrin.h>
#include <unistd.h>

#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>

const QString DOWN_STR = "500 200 500 800";
const QString UP_STR = "500 800 500 200";
const QString LEFT_STR = "500 200 100 200";
const QString RIGHT_STR = "100 200 500 200";

QString program = "/Users/igorgoremykin/Library/Android/sdk/platform-tools//adb";
QStringList arguments = {"shell", "screencap", "-p"};

QMutex mutex;

QHash<int, int> scoreTime = {
    {0 , 400},
    {1 , 400},
    {2 , 400},
    {3 , 400},
    {4 , 383},
    {5 , 383},
    {6 , 383},
    {7 , 366},
    {8 , 366},
    {9 , 366},
    {10, 350},
    {11, 350},
    {12, 350},
    {13, 350},
    {14, 333},
    {15, 333},
    {16, 333},
    {17, 317},
    {18, 317},
    {19, 317},
    {20, 300},
    {21, 300},
    {22, 300},
    {23, 300},
    {24, 283},
    {25, 283},
    {26, 283},
    {27, 266},
    {28, 266},
    {29, 266},
    {30, 250},
    {31, 250},
    {32, 250},
    {33, 250},
    {34, 233},
    {35, 233},
    {36, 233},
    {37, 217},
    {38, 217},
    {39, 217},
    {40, 200},
    {41, 200},
    {42, 200},
    {43, 200},
    {44, 183},
    {45, 183},
    {46, 183},
    {47, 166},
    {48, 166},
    {49, 166},
    {50, 150},
    {51, 150},
    {52, 150},
    {53, 150},
    {54, 150},
    {55, 150},
    {56, 150},  // 58
    {57, 150},  // 61
    // extrapolation
    {58, 150},  // 64
    {59, 150},  // 67
    {60, 133},  // 70
    {61, 133},  // 73
    {62, 133},  // 76
    {63, 133},  // 79
    {64, 83},
    {65, 83},
    {66, 83},
    {67, 66},
    {68, 66},
    {69, 66},
    {70, 50},
    {71, 50},
    {72, 50},
    {73, 50},
    {74, 33},
    {75, 33},
    {76, 33},
    {77, 17},
    {78, 17},
    {79, 17},
};

MonobankSnake::MonobankSnake()
{
    this->screenshotProc = new QProcess();
    this->shouldRebuildCycle = false;
}

void MonobankSnake::run()
{
//    QThread::currentThread()->msleep(2000);
//    QElapsedTimer timer;
//    timer.start();
//    CGRect bounds = {
//        origin: {x: 18, y: 231},
//        size: {width: 328, height: 328}
//    };
//    CGImageRef screenShot = CGWindowListCreateImage(bounds, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
//    QImage imgFromMac = QtMac::fromCGImageRef(screenShot).toImage();
//    CGImageRelease(screenShot);
//    CGDataProviderRef provider = CGImageGetDataProvider(screenShot);
//    CFDataRef rgbData = CGDataProviderCopyData(provider);
//    const uint8 *bytesRaw = CFDataGetBytePtr(rgbData);
//    CFIndex length = CFDataGetLength(rgbData);
//    QPixmap pix;
//    pix.loadFromData(bytesRaw, static_cast<uint>(length), "PNG");
//    QImage imgFromMac((const unsigned char*)bytesRaw, 1920, 2700, QImage::Format_RGB32);
//    QImage imgFromMac(2700, 1920, QImage::Format_ARGB32);
//    for(int i = 0; i < imgFromMac.height(); i++)
//    {
//        for(int u = 0; u < imgFromMac.width(); u++)
//        {
////            qDebug() << i << u << bytesRaw[i * 4 + u];
//            uint index = imgFromMac.height() * 4 * u + i * 4;
//            imgFromMac.setPixelColor(u, i, QColor((int)bytesRaw[index], (int)bytesRaw[index + 1], (int)bytesRaw[index + 2]));
//        }
//    }
//    qDebug() << "imgFromMac->bytesPerLine()" << imgFromMac->bytesPerLine();
//    for (int y = 0; y < imgFromMac.height(); y++)
//    {
//        memcpy(imgFromMac.scanLine(y), &bytesRaw[y * imgFromMac.bytesPerLine()], imgFromMac.bytesPerLine());
//    }
//    QImage imgFromMac = QtMac::fromCGImageRef(screenShot).toImage();
//    CGImageRelease(screenShot);
//    qDebug() << "Elapse step:" << timer.elapsed();
//    QDateTime dtImgFromMac = QDateTime::currentDateTime();
//    qint64 msSEImgFromMac = dtImgFromMac.toMSecsSinceEpoch();
//    bool saved = imgFromMac.save(QString("/Users/igorgoremykin/projects/hellkitty/monobanksnake/logs/%1.png").arg(msSEImgFromMac), "PNG");
//    qDebug() << "saved" << saved << imgFromMac.isNull();

//    return;
//    QThread::currentThread()->msleep(2000);
    QString program1 = "/Users/igorgoremykin/Library/Android/sdk/platform-tools//adb";
    QStringList arguments1;
    arguments1 << "shell" << "input" << "swipe" << "550 1000 550 1000" << "1000";

    QProcess *moveProc = new QProcess();
    moveProc->start(program1, arguments1);
    moveProc->waitForFinished();
    QThread::currentThread()->msleep(2000);
    QString program2 = "/Users/igorgoremykin/Library/Android/sdk/platform-tools//adb";
    QStringList arguments2;
    arguments2 << "shell" << "input" << "tap" << "550" << "1280";

    QProcess *moveProc2 = new QProcess();
    moveProc2->start(program2, arguments2);
    moveProc2->waitForFinished();

    QElapsedTimer timer1;
    timer1.start();

    this->click(150, 300);
    this->click(150, 300);

    while (true)
    {
        if (timer1.elapsed() < 5265)
            continue;
        qDebug() << "Elapse step:" << timer1.elapsed();
        timer1.restart();
        break;
    }


//    QThread::currentThread()->msleep(4000);

//    system("#/bin/bash\n/Users/igorgoremykin/Library/Android/sdk/platform-tools//adb shell screencap -p");

//    this->screenshotProc->start(program, arguments);
//    this->screenshotProc->waitForFinished();

//    qDebug() << "The slow operation 1 took" << timer1.elapsed();
    timer1.restart();

//    QImage img(QString("/Users/igorgoremykin/projects/build-hellkitty-Desktop_Qt_5_12_0_clang_64bit-Release/monobanksnake/screenshots/6.png"), "PNG");
//    QImage img = QImage::fromData(this->screenshotProc->readAllStandardOutput());

    CGRect bounds = {
        origin: {x: 18, y: 231},
        size: {width: 327, height: 327}
    };
    CGImageRef screenShot = CGWindowListCreateImage(bounds, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
    QImage img = QtMac::fromCGImageRef(screenShot).toImage().scaled(972, 972);
    CGImageRelease(screenShot);
    qDebug() << timer1.elapsed();

//    QPixmap pixmap = QPixmap();
//    QScreen *screen = QGuiApplication::primaryScreen();
//    pixmap = screen->grabWindow(0, 0, 0, 400, 609);
//    qDebug() << timer1.elapsed();
//    QImage img = pixmap.toImage().copy(36, 462, 655, 655);
//    QDateTime dt = QDateTime::currentDateTime();
//    qint64 msSE = dt.toMSecsSinceEpoch();
//    img.save(QString("/Users/igorgoremykin/projects/hellkitty/monobanksnake/logs/%1.png").arg(msSE), "PNG");
//    qDebug() << "Image saved";
    MapRecognizer recognizer = MapRecognizer(img);
    recognizer.recognize();

    this->food = Pos(recognizer.food.y, recognizer.food.x);
    this->obstacle = Pos(recognizer.obstacle.y, recognizer.obstacle.x);

//    qDebug() << "The slow operation 2 took" << timer1.elapsed();

//    connect(this->screenshotProc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
//            [=](int exitCode, QProcess::ExitStatus exitStatus){
////        this->onNewScreenshot();
//        qDebug() << "onNewScreenshot";
//    });
//    this->screenshotProc->start(program, arguments);

    QList<PointType> init_types = {
        PointType::HEAD_R,
        PointType::BODY_HOR,
        PointType::BODY_HOR,
        PointType::BODY_HOR
    };

    Map map = Map(17, 17);
    map.create_food(this->food);
    Snake *snake = new Snake(map, DirecType::RIGHT,
                        this->reversed(recognizer.catBodies),
                        init_types);

    qDebug() << "food:" << this->food.toString();
    qDebug() << "bodies size:" << snake->bodies.size();
    qDebug() << "bodies" << snake->bodies[0].toString() << snake->bodies[1].toString() << snake->bodies[2].toString() << snake->bodies[3].toString();
    qDebug() << "direc:" << Direc::toString(DirecType::RIGHT);

//    timer1.restart();

    qDebug() << timer1.elapsed();

    int stepTime = 400;
    int score = 0;

    QList<Pos> prevCatBodies;

    QImage nextCell;
    short xShift = 1;
    short yShift = 0;

    CustomSolver *customSolver = new CustomSolver(*snake);
    bool fakeFood = false;
    int fakeFoodIndex = 0;
    QList<Pos> fakeFoodList = {
//        Pos(15, 1),
        Pos(15, 15),
        Pos(2, 15)
    };
    bool removeSnakeTail = false;
    bool customSolverEnabled = false;
    int initialBoost = 30;

//    ScreenshotWorker *sw = new ScreenshotWorker();
//    sw->setAutoDelete(false);
//    QThreadPool::globalInstance()->start(sw);

    while (true)
    {
        QElapsedTimer timer;
        timer.start();

        QElapsedTimer timer2;
        timer2.start();

        CGRect bounds = {
            origin: {x: 18, y: 231},
            size: {width: 327, height: 327}
        };
        CGImageRef screenShot = CGWindowListCreateImage(bounds, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
        QImage img2 = QtMac::fromCGImageRef(screenShot).toImage().scaled(972, 972);
        CGImageRelease(screenShot);
        qint64 elapsedScreenshot = timer2.elapsed();

        MapRecognizer recognizer = MapRecognizer(img2);
        recognizer.recognize();

        this->obstacle = Pos(recognizer.obstacle.y, recognizer.obstacle.x);
        if (fakeFood)
        {
//            this->food = Pos(2, 15);
            this->food = fakeFoodList[fakeFoodIndex];
        }
        else
        {
            this->food = Pos(recognizer.food.y, recognizer.food.x);
        }

        if (map.has_food())
            map.rm_food();
        if (this->food != Pos(-1, -1))
        {
            map.create_food(this->food);
        }

        if (map.has_obstacle())
            map.rm_obstacle();
        if (this->obstacle.x != -1 && this->obstacle.y != -1)
        {
            map.create_obstacle(this->obstacle);
        }

        Pos head = snake->head();
        QImage currCell = img2.copy((head.y - 1) * 65 + 30, (head.x - 1) * 65 + 30, 5, 5);

//        QDateTime dt = QDateTime::currentDateTime();
//        qint64 msSE = dt.toMSecsSinceEpoch();
//        qDebug() << "currCell: " << msSE << head;
//        currCell.save(QString("/Users/igorgoremykin/projects/hellkitty/monobanksnake/logs/%1_currCell_.png").arg(msSE), "PNG");

        if (nextCell != currCell)
        {
//            qDebug() << "Elapse screenshot:" << elapsedScreenshot;

            prevCatBodies = recognizer.catBodies;
//            qDebug() << "Snake moved";

            mutex.lock();
            DirecType new_direc;
            if (!customSolverEnabled && snake->bodies.size() <= (initialBoost + 4 + fakeFoodList.size()))
            {
                if (snake->bodies.size() == (initialBoost + 4))
                {
                    fakeFood = true;
                }
                if (snake->bodies.size() == (initialBoost + 4 + fakeFoodList.size()))
                {
                    customSolverEnabled = true;
                }
                if (snake->bodies.size() >= (initialBoost + 4) && snake->bodies.size() < (initialBoost + 4 + fakeFoodList.size()) && snake->head() == fakeFoodList[fakeFoodIndex])
                {
                    fakeFoodIndex++;
                }
                GreedySolver solver = GreedySolver(*snake);
                new_direc = solver.next_direc(score > 0);
//                qDebug() << "Snake direc:" << Direc::toString(new_direc) << Direc::toString(snake->direc);
                if (Direc::opposite(new_direc) == snake->direc)
                {
                    PathSolver path_solver1(*snake);
                    new_direc = path_solver1.longest_path_to_tail()[0];
//                    qDebug() << "Snake new direc:" << Direc::toString(new_direc) << Direc::toString(snake->direc);
                }
//                qDebug() << "Fake food direc 1:" << Direc::toString(new_direc) << snake->head() << this->food.toString();
//                qDebug() << "Snake bodies:" << snake->bodies.size() << snake->bodies;
                if (snake->bodies.size() == (initialBoost + 4 + fakeFoodList.size()) && snake->head() == fakeFoodList[fakeFoodIndex] && new_direc == DirecType::DOWN)
                {
                    new_direc = DirecType::UP;
                }
            }
            else
            {
                if (fakeFood)
                {
                    removeSnakeTail = true;
                }
                fakeFood = false;
                new_direc = customSolver->next_direc();
//                qDebug() << "Custom solver direc 0:" << Direc::toString(new_direc) << snake->head() << this->food.toString();
//                qDebug() << "Snake bodies:" << snake->bodies.size() << snake->bodies;
            }
            mutex.unlock();

            snake->move(new_direc);
            if (removeSnakeTail)
            {
                snake->rm_tail();
                snake->rm_tail();
//                snake->rm_tail();
                customSolverEnabled = true;
                removeSnakeTail = false;
            }

            Pos head = snake->head();
//            qDebug() << "New snake head:" << snake->head().y << snake->head().x << (head.y - 1) * 65 + 30 << (head.x - 1) * 65 + 30 << Direc::toString(snake->direc);
            nextCell = img2.copy((head.y - 1) * 65 + 30, (head.x - 1) * 65 + 30, 5, 5);
//            qDebug() << "obstacle:" << this->obstacle;

//            QDateTime dt = QDateTime::currentDateTime();
//            qint64 msSE = dt.toMSecsSinceEpoch();
//            qDebug() << "nextCell: " << msSE << head;
//            img2.save(QString("/Users/igorgoremykin/projects/hellkitty/monobanksnake/logs/%1.png").arg(msSE), "PNG");

//            timer2.restart();
//            this->swipe(150, 300, new_direc);
//            this->mousePress(150, 300);
//            int xShift = 0;
//            int yShift = 0;

//            switch (new_direc)
//            {
//            case DirecType::UP:
//                yShift = -50;
//                break;
//            case DirecType::DOWN:
//                yShift = 50;
//                break;
//            case DirecType::LEFT:
//                xShift = -50;
//                break;
//            case DirecType::RIGHT:
//                xShift = 50;
//                break;
//            }
//            this->mouseMoveFromTo(150, 300, 150 + xShift, 300 + yShift);
//            this->mouseRelease();
            this->swipe(150, 300, new_direc);
            this->swipe(150, 300, new_direc);
//            this->swipe(150, 300, new_direc);

//            qDebug() << "Swipe time:" << timer2.elapsed();
//            qDebug() << "Total time:" << timer.elapsed();

//            qDebug() << '\n';
        }
    }
}

void MonobankSnake::click(int x, int y)
{
    CGEventRef click1_down = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseDown,
                CGPointMake(x, y),
                kCGMouseButtonLeft
                );
    CGEventRef click1_up = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseUp,
                CGPointMake(x, y),
                kCGMouseButtonLeft
                );

    usleep(1 * 10000);
    CGEventPost(kCGHIDEventTap, click1_down);
    usleep(1 * 10000);
    CGEventPost(kCGHIDEventTap, click1_up);

    // Release the events
    CFRelease(click1_up);
    CFRelease(click1_down);
}

void MonobankSnake::swipe(int x, int y, DirecType direc)
{
    usleep(100);
    CGEventRef click1_down = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseDown,
                CGPointMake(x, y),
                kCGMouseButtonLeft
                );

    CGEventSetType(click1_down, kCGEventLeftMouseDown);
    CGEventPost(kCGHIDEventTap, click1_down);
    CFRelease(click1_down);
    usleep(100);
    int xShift = 0;
    int yShift = 0;

    switch (direc)
    {
    case DirecType::UP:
        yShift = -50;
        break;
    case DirecType::DOWN:
        yShift = 50;
        break;
    case DirecType::LEFT:
        xShift = -50;
        break;
    case DirecType::RIGHT:
        xShift = 50;
        break;
    }

//    qDebug() << "swipe" << xShift << yShift;

    CGEventRef move = CGEventCreateMouseEvent(
                NULL, kCGEventMouseMoved,
                CGPointMake(x + xShift, y + yShift),
                kCGMouseButtonCenter // ignored
                );
    CGEventSetType(move, kCGEventMouseMoved);
    CGEventPost(kCGHIDEventTap, move);
    CFRelease(move);

    usleep(2 * 10000);

    CGEventRef click1_up = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseUp,
                CGPointMake(x + xShift, y + yShift),
                kCGMouseButtonLeft
                );
//    CGPoint pt;
//    pt.x = x;
//    pt.y = y - 30;
//    CGWarpMouseCursorPosition(pt);
    CGEventSetType(click1_up, kCGEventLeftMouseUp);
    CGEventPost(kCGHIDEventTap, click1_up);
    CFRelease(click1_up);
}

void MonobankSnake::mouseMoveFromTo(int pX0, int pY0, int pX1, int pY1)
{
  int stepsize = 50;

  int xSteps = (pX1 - pX0) / stepsize;
  int ySteps = (pY1 - pY0) / stepsize;

  int steps = std::max(std::max(abs(xSteps), abs(ySteps)), 1);

  int xStep = (pX1 - pX0) / steps;
  int yStep = (pY1 - pY0) / steps;

  for(int i = 0; i < steps; i++)
  {
    int xi = pX0 + i * xStep;
    int yi = pY0 + i * yStep;
    mouseMoveTo(xi, yi);
    // usleep(10000);
  }

  mouseMoveTo(pX1, pY1);
  // usleep(10000);
}

void MonobankSnake::mouseMoveTo(int pX, int pY)
{
  CGPoint newloc;
  CGEventRef eventRef;

  newloc.x = pX;
  newloc.y = pY;

  eventRef = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, newloc,
    kCGMouseButtonCenter);
  CGEventSetType(eventRef, kCGEventMouseMoved);
  CGEventPost(kCGSessionEventTap, eventRef);
  CFRelease(eventRef);
}

void MonobankSnake::mousePress(int x, int y)
{
  CGPoint curloc;
  CGEventRef eventRef;

  CGEventRef ourEvent = CGEventCreate(NULL);
  curloc = CGEventGetLocation(ourEvent);
  CFRelease(ourEvent);

  eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, CGPointMake(x, y),
    kCGMouseButtonCenter);

  CGEventSetType(eventRef, kCGEventLeftMouseDown);
  CGEventPost(kCGSessionEventTap, eventRef);
  CFRelease(eventRef);
}

void MonobankSnake::mouseRelease()
{
  CGPoint curloc;
  CGEventRef eventRef;

  CGEventRef ourEvent = CGEventCreate(NULL);
  curloc = CGEventGetLocation(ourEvent);
  CFRelease(ourEvent);

  eventRef = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, curloc,
    kCGMouseButtonCenter);

  CGEventSetType(eventRef, kCGEventLeftMouseUp);
  CGEventPost(kCGSessionEventTap, eventRef);
  CFRelease(eventRef);
}

void MonobankSnake::onNewScreenshot()
{
    QImage img = QImage::fromData(this->screenshotProc->readAllStandardOutput());
    MapRecognizer recognizer = MapRecognizer(img);
    recognizer.recognize();

    this->food = Pos(recognizer.food.y, recognizer.food.x);
    this->obstacle = recognizer.obstacle;

    qDebug() << "New screenshot";

    this->screenshotProc->start(program, arguments);
}

QList<Pos> MonobankSnake::reversed(const QList<Pos> & in) {
    QList<Pos> result;
    for (int i = in.size() - 1; i >= 0; --i)
    {
        Pos cur = in[i];
        result << Pos(cur.y, cur.x);
    }
    return result;
}

ScreenshotWorker::ScreenshotWorker()
{
}

void ScreenshotWorker::run()
{
    while (true)
    {
        QString program2 = "/Users/igorgoremykin/Library/Android/sdk/platform-tools//adb";
        QStringList arguments2;
        arguments2 << "shell" << "input" << "tap" << "550" << "1280";
        QProcess p;
        p.start(program2, arguments2);
        p.waitForFinished();
        qDebug() << "ScreenshotWorker::run tap";
        QThread::sleep(100);
    }
}
