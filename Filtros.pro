#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T18:07:06
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Filtros
TEMPLATE = app

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
        filtro_passivo.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS += \
        filtro_passivo.h \
        mainwindow.h \
        qcustomplot.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Imagens/pa_rc.png \
    Imagens/pa_rl.png \
    Imagens/passa_faixa.png \
    Imagens/pb_rc.png \
    Imagens/pb_rl.png \
    Imagens/rejeita_faixa.png

RESOURCES += \
    pics.qrc
