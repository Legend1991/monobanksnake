#include "maprecognizer.h"

#include <QDebug>
#include <QDateTime>

const QList<QColor> obstacleColorList = {
    QColor(0, 136, 67),
    QColor(0, 133, 74),
    QColor(0, 138, 71),
    QColor(0, 139, 72)
};
const QColor catHeadColor = QColor(126, 55, 55);

const QString pathToCatIamge = QString("/Users/igorgoremykin/projects/build-hellkitty-Desktop_Qt_5_12_0_clang_64bit-Release/monobanksnake/screenshots/cat.png");
const QImage catImage(pathToCatIamge, "PNG");

MapRecognizer::MapRecognizer(QImage img): img(img)
{
    food = Pos(-1, -1);
    obstacle = Pos(-1, -1);
    this->direc = DirecType::NONE;
}

void MapRecognizer::recognize()
{
    int fieldHeight = 972;
    int fieldWidth = 972;
    int yOffset = 0;
    int xOffset = 0;
    int cellOffset = 31;
    int step = 65;

    bool foodIsFound = false;

    for (int x = xOffset; x < (fieldWidth + xOffset) && x < img.width(); x += step)
    {
        for (int y = yOffset; y < (fieldHeight + yOffset) && y < img.height(); y += step)
        {
            Pos curPos = Pos((x - xOffset) / step + 1, (y - yOffset) / step + 1);
            QColor color = img.pixelColor(x + cellOffset, y + cellOffset);
            if (this->isObstacle(color))
            {
                this->obstacle = curPos;
                continue;
            }
            if (this->isCat(color))
            {
                this->catBodies << curPos;
                this->catTypes << PointType::BODY_VER;
                this->checkCatHead(x, y);
                continue;
            }
            bool res = this->isFood(color);
            if (foodIsFound == false && res)
            {
                foodIsFound = res;
                this->food = curPos;
                if (curPos.x == 1 && curPos.y == 1 && color == QColor(154, 156, 157))
                {
                    exit(0);
                }
            }
        }
    }
    //    this->fixCatTypes();
//    if (foodIsFound == false)
//    {
//        for (int x = xOffset; x < fieldWidth + xOffset; x += step)
//        {
//            for (int y = yOffset; y < fieldHeight + yOffset; y += step)
//            {
//                QColor color = img.pixelColor(x + cellOffset, y + cellOffset);
//                //            qDebug() << color.red() << color.green() << color.blue();
//                //            if (banks.contains(color))
//                //            {
//                qDebug() << "x:" << (x - xOffset) / step
//                         << "\ty:" << (y - yOffset) / step
//                         << "\t" << color.red() << color.green() << color.blue()
//                         << "\t" << this->isCat(color);
//                //            }
//            }
//        }
////        exit(0);
//    }
}

bool MapRecognizer::isObstacle(QColor color)
{
    if (color.red() >= 0 && color.red() <= 5
            && color.green() >= 130 && color.green() <= 142
            && color.blue() >= 60 && color.blue() <= 75)
    {
//        qDebug() << "Obstacle";
        return true;
    }

    return false;
}

bool MapRecognizer::isFood(QColor color)
{
    if (color.red() >= 19 && color.red() <= 189
            && color.green() >= 185 && color.green() <= 233
            && color.blue() >= 86 && color.blue() <= 193)
    {
//        qDebug() << "Green circle";
        return true;
    }

    if (color.red() >= 105 && color.red() <= 245
            && color.green() >= 100 && color.green() <= 232
            && color.blue() >= 55 && color.blue() <= 142)
    {
//        qDebug() << "Райфайзен банка";
        return true;
    }

    if (color.red() >= 0 && color.red() <= 0
            && color.green() >= 83 && color.green() <= 87
            && color.blue() >= 58 && color.blue() <= 62)
    {
//        qDebug() << "Украинская банка";
        return true;
    }

    if (color.red() >= 0 && color.red() <= 36
            && color.green() >= 141 && color.green() <= 171
            && color.blue() >= 13 && color.blue() <= 75)
    {
//        qDebug() << "Укрсиб";
        return true;
    }

    if (color.red() >= 122 && color.red() <= 225
            && color.green() >= 202 && color.green() <= 255
            && color.blue() >= 62 && color.blue() <= 210)
    {
//        qDebug() << "Green square";
        return true;
    }

    if (color.red() >= 0 && color.red() <= 154
            && color.green() >= 70 && color.green() <= 191
            && color.blue() >= 138 && color.blue() <= 224)
    {
//        qDebug() << "Израиль";
        return true;
    }

    if (color.red() >= 239 && color.red() <= 255
            && color.green() >= 135 && color.green() <= 221
            && color.blue() >= 0 && color.blue() <= 203)
    {
//        qDebug() << "Orange arrow";
        return true;
    }

    if (color.red() >= 0 && color.red() <= 15
            && color.green() >= 70 && color.green() <= 115
            && color.blue() >= 130 && color.blue() <= 175)
    {
//        qDebug() << "Blue triangle";
        return true;
    }

    if (color.red() >= 238 && color.red() <= 255
            && color.green() >= 0 && color.green() <= 207
            && color.blue() >= 2 && color.blue() <= 235)
    {
//        qDebug() << "Alafa bank";
        return true;
    }

    if (color.red() >= 65 && color.red() <= 195
            && color.green() >= 175 && color.green() <= 225
            && color.blue() >= 58 && color.blue() <= 175)
    {
//        qDebug() << "Privat";
        return true;
    }

    if (color.red() >= 208 && color.red() <= 237
            && color.green() >= 25 && color.green() <= 153
            && color.blue() >= 25 && color.blue() <= 158)
    {
//        qDebug() << "Pumb";
        return true;
    }

    return false;
}

bool MapRecognizer::isCat(QColor color)
{
    return color.red() == color.green()
            && color.green() == color.blue();

//    for (int x = 0; x < catImage.width(); ++x)
//        for (int y = 0; y < catImage.height(); ++y)
//            if (catImage.pixelColor(x, y) == color)
//                return true;
//    return false;
}

void MapRecognizer::checkCatHead(int x, int y)
{
    if (this->direc != DirecType::NONE)
        return;

    int catHeadRightOffset = 58;
    int catHeadLeftOffset = 7;
    int catHeadUpOffset = 2;
    int catHeadDownOffset = 61;
    int cellOffset = 31;

    QColor catHeadRightColor = img.pixelColor(x + catHeadRightOffset, y + cellOffset);
    QColor catHeadLeftColor = img.pixelColor(x + catHeadLeftOffset, y + cellOffset);
    QColor catHeadUpColor = img.pixelColor(x + cellOffset, y + catHeadUpOffset);
    QColor catHeadDownColor = img.pixelColor(x + cellOffset, y + catHeadDownOffset);

    if (catHeadRightColor == catHeadColor)
    {
        qDebug() << "catHeadRightColor" << x << y;
        this->direc = DirecType::RIGHT;
        this->catTypes.last() = PointType::HEAD_R;
    }
    else if (catHeadLeftColor == catHeadColor)
    {
        qDebug() << "catHeadLeftColor" << x << y;
        this->direc = DirecType::LEFT;
        this->catTypes.last() = PointType::HEAD_L;
    }
    else if (catHeadUpColor == catHeadColor)
    {
        qDebug() << "catHeadUpColor" << x << y;
        this->direc = DirecType::UP;
        this->catTypes.last() = PointType::HEAD_U;
    }
    else if (catHeadDownColor == catHeadColor)
    {
        qDebug() << "catHeadDownColor" << x << y;
        this->direc = DirecType::DOWN;
        this->catTypes.last() = PointType::HEAD_D;
    }
}

void MapRecognizer::fixCatTypes()
{
    for (int i = 0; i < this->catTypes.size(); ++i)
    {
        if (this->catTypes[i] == PointType::HEAD_U
                || this->catTypes[i] == PointType::HEAD_D
                || this->catTypes[i] == PointType::HEAD_L
                || this->catTypes[i] == PointType::HEAD_R)
        {
            continue;
        }

        int p = i > 0 ? i - 1 : i;
        int n = i < this->catTypes.size() - 1 ? i + 1 : i;

        if (this->catBodies[p].y == this->catBodies[n].y)
        {
            this->catTypes[i] = PointType::BODY_HOR;
        }
        else if (this->catBodies[p].x == this->catBodies[i].x && this->catBodies[i].y == this->catBodies[n].y)
        {
            if (this->catBodies[p].y == this->catBodies[i].y - 1 && this->catBodies[i].x + 1 == this->catBodies[n].x)
            {
                this->catTypes[i] = PointType::BODY_RD;
            }
        }
    }
}

const QVector<QColor> banks = {
    QColor(19, 189, 86), // Green circle
    QColor(62, 197, 104), // Green circle
    QColor(87, 185, 99), // Green circle
    QColor(92, 188, 103), // Green circle
    QColor(108, 195, 117), // Green circle
    QColor(180, 229, 186), // Green circle
    QColor(133, 207, 142), // Green circle
    QColor(173, 226, 179), // Green circle
    QColor(180, 229, 185), // Green circle
    QColor(179, 229, 185), // Green circle
    QColor(143, 212, 151), // Green circle
    QColor(166, 223, 173), // Green circle
    QColor(149, 214, 156), // Green circle
    QColor(169, 224, 175), // Green circle
    QColor(187, 232, 192), // Green circle
    QColor(189, 233, 193), // Green circle
    QColor(171, 224, 177), // Green circle
    QColor(178, 228, 183), // Green circle

    QColor(124, 115, 63), // Райфайзен банка
    QColor(241, 227, 123), // Райфайзен банка
    QColor(97, 90, 50), // Райфайзен банка
    QColor(128, 121, 73), // Райфайзен банка
    QColor(129, 121, 74), // Райфайзен банка
    QColor(145, 137, 83), // Райфайзен банка
    QColor(179, 169, 102), // Райфайзен банка
    QColor(239, 226, 137), // Райфайзен банка
    QColor(162, 153, 93), // Райфайзен банка
    QColor(234, 221, 134), // Райфайзен банка
    QColor(222, 209, 127), // Райфайзен банка
    QColor(212, 200, 122), // Райфайзен банка
    QColor(213, 201, 122), // Райфайзен банка
    QColor(215, 203, 123), // Райфайзен банка
    QColor(227, 215, 130), // Райфайзен банка
    QColor(207, 196, 119), // Райфайзен банка
    QColor(220, 208, 126), // Райфайзен банка
    QColor(238, 225, 137), // Райфайзен банка

    QColor(0, 86, 62),     // Украинская банка
    QColor(0, 83, 58),     // Украинская банка
    QColor(0, 81, 60),     // Украинская банка
    QColor(0, 87, 58),     // Украинская банка

    QColor(0, 171, 75),    // Укрсиб
    QColor(0, 168, 72),    // Укрсиб
    QColor(0, 168, 69),    // Укрсиб
    QColor(0, 145, 13),    // Укрсиб
    QColor(0, 149, 25),    // Укрсиб
    QColor(0, 154, 41),    // Укрсиб
    QColor(36, 159, 71),    // Укрсиб
    QColor(31, 156, 68),    // Укрсиб
    QColor(30, 156, 67),    // Укрсиб
    QColor(1, 141, 42),    // Укрсиб
    QColor(26, 154, 63),   // Укрсиб
    QColor(11, 146, 50),   // Укрсиб
    QColor(9, 145, 49),    // Укрсиб

    QColor(218, 250, 202), // Green square
    QColor(214, 249, 198), // Green square
    QColor(211, 248, 193), // Green square
    QColor(125, 205, 66), // Green square
    QColor(216, 244, 194), // Green square
    QColor(142, 213, 90),  // Green square
    QColor(168, 224, 127), // Green square
    QColor(221, 247, 202), // Green square
    QColor(205, 240, 179), // Green square
    QColor(211, 242, 187), // Green square
    QColor(189, 233, 157), // Green square
    QColor(133, 209, 78), // Green square

    QColor(149, 191, 224),  // Израиль
    QColor(0, 70, 138),  // Израиль
    QColor(0, 74, 141),  // Израиль
    QColor(25, 89, 147),  // Израиль
    QColor(154, 188, 220),  // Израиль
    QColor(42, 102, 157),  // Израиль
    QColor(151, 186, 218),  // Израиль
    QColor(144, 194, 226),  // Израиль
    QColor(75, 127, 175),  // Израиль
    QColor(92, 140, 184),  // Израиль
    QColor(125, 165, 203), // Израиль
    QColor(138, 176, 211), // Израиль
    QColor(140, 177, 212), // Израиль
    QColor(137, 175, 210), // Израиль
    QColor(141, 178, 212), // Израиль
    QColor(108, 153, 193), // Израиль

    QColor(254, 135, 0),   // Orange arrow
    QColor(246, 209, 174), // Orange arrow
    QColor(245, 211, 179), // Orange arrow
    QColor(244, 209, 176), // Orange arrow
    QColor(242, 223, 205), // Orange arrow
    QColor(245, 206, 171), // Orange arrow
    QColor(244, 210, 177), // Orange arrow
    QColor(239, 221, 203), // Orange arrow
    QColor(239, 219, 198), // Orange arrow
    QColor(239, 216, 191), // Orange arrow
    QColor(239, 220, 200), // Orange arrow
    QColor(239, 214, 189), // Orange arrow
    QColor(239, 200, 160), // Orange arrow
    QColor(239, 191, 141), // Orange arrow
    QColor(239, 211, 181), // Orange arrow
    QColor(240, 202, 161), // Orange arrow
    QColor(240, 209, 177), // Orange arrow
    QColor(239, 181, 121), // Orange arrow
    QColor(240, 214, 187), // Orange arrow
    QColor(239, 214, 187), // Orange arrow
    QColor(239, 210, 180), // Orange arrow
    QColor(239, 194, 149), // Orange arrow
    QColor(240, 213, 186), // Orange arrow

    QColor(0, 109, 171),    // Blue triangle
    QColor(0, 86, 156),    // Blue triangle
    QColor(12, 92, 155),    // Blue triangle
    QColor(9, 77, 138),    // Blue triangle
    QColor(6, 87, 152),    // Blue triangle
    QColor(3, 85, 151),    // Blue triangle
    QColor(0, 83, 149),    // Blue triangle
    QColor(1, 84, 149),    // Blue triangle
    QColor(2, 85, 150),    // Blue triangle

    QColor(255, 0, 2),   // Alafa bank
    QColor(255, 52, 229),   // Alafa bank
    QColor(255, 0, 6),   // Alafa bank
    QColor(255, 0, 8),   // Alafa bank
    QColor(255, 0, 14),   // Alafa bank
    QColor(255, 0, 16),   // Alafa bank
    QColor(255, 6, 26),   // Alafa bank
    QColor(255, 24, 34),   // Alafa bank
    QColor(255, 103, 102),   // Alafa bank
    QColor(254, 172, 169),   // Alafa bank
    QColor(243, 207, 205),   // Alafa bank
    QColor(238, 50, 44),   // Alafa bank
    QColor(238, 57, 50),   // Alafa bank
    QColor(238, 60, 53),   // Alafa bank
    QColor(238, 65, 58),   // Alafa bank
    QColor(238, 74, 67),   // Alafa bank
    QColor(242, 180, 177), // Alafa bank
    QColor(242, 191, 188), // Alafa bank
    QColor(240, 106, 101), // Alafa bank
    QColor(240, 115, 110), // Alafa bank
    QColor(239, 93,  87),  // Alafa bank
    QColor(239, 87, 81),   // Alafa bank

    QColor(68, 194, 62), // Privat
    QColor(70, 195, 65), // Privat
    QColor(72, 195, 66), // Privat
    QColor(82, 175, 135), // Privat
    QColor(74, 195, 66), // Privat
    QColor(46, 190, 45), // Privat
    QColor(114, 193, 91), // Privat
    QColor(190, 221, 173), // Privat
    QColor(157, 210, 138), // Privat
    QColor(159, 210, 139), // Privat
    QColor(145, 204, 125), // Privat
    QColor(124, 197, 102), // Privat
    QColor(117, 194, 95),  // Privat
    QColor(155, 208, 135), // Privat

    QColor(237, 102, 113), // Pumb
    QColor(236, 100, 112), // Pumb
    QColor(235, 88, 103), // Pumb
    QColor(225, 25, 25), // Pumb
    QColor(234, 91, 104), // Pumb
    QColor(226, 29, 57), // Pumb
    QColor(244, 153, 161), // Pumb
    QColor(231, 153, 158), // Pumb
    QColor(230, 148, 153), // Pumb
    QColor(228, 142, 147), // Pumb
    QColor(227, 137, 143), // Pumb
    QColor(208, 55, 65), // Pumb
    QColor(223, 122, 128), // Pumb
    QColor(219, 104, 111), // Pumb
    QColor(222, 115, 122), // Pumb
    QColor(220, 107, 114), // Pumb
    QColor(221, 111, 117), // Pumb
    QColor(218, 96, 104),  // Pumb
    QColor(208, 56, 66),   // Pumb
    QColor(211, 68, 77)    // Pumb
};
