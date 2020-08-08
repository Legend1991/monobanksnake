#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QTest>
#include <QList>
#include <QThread>

#include "monobanksnake.h"
#include "maprecognizertest.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
//        MainWindow w;
//        w.show();

    MonobankSnake snake;
    snake.run();
    return 0;

//    a.setAttribute(Qt::AA_Use96Dpi, true);
//    MapRecognizerTest mrt;
//    QTEST_SET_MAIN_SOURCE_PATH
//    return QTest::qExec(&mrt, argc, argv);

    return a.exec();
}
