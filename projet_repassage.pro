#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------
QT       += widgets quickwidgets
QT       += core gui sql printsupport
QT       += charts
QT       += serialport
QT       += core gui multimedia multimediawidgets sql location \
    quick
QT += widgets charts
QT       += qml quick

QT       += core gui sql \
quick
QT       += core gui charts
QT      += printsupport
QT  += core network
QT       += core gui network
QT  +=svg
QT += quick
QT += core gui multimedia multimediawidgets
QT += multimedia
QT       += core gui  serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet_repassage
TEMPLATE = app
QT += sql
QT += core gui
QT += core gui charts
QT += multimedia

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
SOURCES += \
    chatserver.cpp \
    chatsocket.cpp \
    connection.cpp \
    dumessengerconnectiondialog.cpp \
    eleve.cpp \
    enseignant.cpp \
    exportexcel.cpp \
    garderiew.cpp \
    main.cpp \
    smtp.cpp

HEADERS += \
    chatserver.h \
    chatsocket.h \
    connection.h \
    dumessengerconnectiondialog.h \
    eleve.h \
    enseignant.h \
    exportexcel.h \
    garderiew.h \
    smtp.h

FORMS += \
    dumessengerconnectiondialog.ui \
    garderiew.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sons.qrc

win32: LIBS += -L"C:\Users\user\Desktop\projet_repassage" -llibeay32 -lssleay32

DISTFILES += \
    libeay32.dll \
    smtp.exe \
    ssleay32.dll




