QT += core gui
QT += testlib
QT += macextras

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += testcase
LIBS += -framework ApplicationServices

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        basesolver.cpp \
        customsolver.cpp \
        direc.cpp \
        greedysolver.cpp \
        hamiltonsolver.cpp \
        linearsolver.cpp \
        main.cpp \
        map.cpp \
        maprecognizer.cpp \
        maprecognizertest.cpp \
        monobanksnake.cpp \
        pathsolver.cpp \
        point.cpp \
        pos.cpp \
        snake.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    basesolver.h \
    customsolver.h \
    direc.h \
    greedysolver.h \
    hamiltonsolver.h \
    linearsolver.h \
    map.h \
    maprecognizer.h \
    maprecognizertest.h \
    monobanksnake.h \
    pathsolver.h \
    point.h \
    pos.h \
    snake.h

DISTFILES += \
    screenshots/cat.png \
    screenshots/0.png \
    screenshots/1.png \
    screenshots/2.png \
    screenshots/3.png \
    screenshots/4.png \
    screenshots/5.png \
    screenshots/6.png \
    screenshots/7.png \
    screenshots/8.png \
    screenshots/9.png \
    screenshots/10.png \
    screenshots/11.png

copydata.commands = $(COPY_DIR) $$PWD/screenshots $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
