QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avistamento.cpp \
    equipamento.cpp \
    imagem.cpp \
    local.cpp \
    local_ui.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    planet.cpp \
    astro.cpp \
    comet.cpp \
    publicacao.cpp \
    publicacao_ui.cpp \
    registro.cpp \
    solar-system.cpp \
    star.cpp \
    tipoequipamento.cpp \
    usuario.cpp

HEADERS += \
    avistamento.h \
    equipamento.h \
    imagem.h \
    local.h \
    local_ui.h \
    login.h \
    mainwindow.h \
    planet.hpp \
    comet.hpp \
    astro.hpp \
    publicacao.h \
    publicacao_ui.h \
    registro.h \
    star.hpp \
    solar-system.hpp \
    tipoequipamento.h \
    usuario.h

FORMS += \
    local_ui.ui \
    login.ui \
    mainwindow.ui \
    publicacao_ui.ui \
    registro.ui

# Default rules for deployment.
INCLUDEPATH += "C:\Program Files\PostgreSQL\15\include"
LIBS += "C:\Program Files\PostgreSQL\15\lib\libpq.lib"
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resouces.qrc
