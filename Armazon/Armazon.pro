QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alistador.cpp \
    articulo.cpp \
    balanceador.cpp \
    cliente.cpp \
    cola.cpp \
    controlfabricasthread.cpp \
    empacador.cpp \
    fabricasthread.cpp \
    facturacionthread.cpp \
    funciones.cpp \
    main.cpp \
    mainwindow.cpp \
    pedido.cpp \
    pedidosthread.cpp

HEADERS += \
    alistador.h \
    articulo.h \
    balanceador.h \
    cliente.h \
    cola.h \
    controlfabricasthread.h \
    empacador.h \
    fabricasthread.h \
    facturacionthread.h \
    funciones.h \
    mainwindow.h \
    pedido.h \
    pedidosthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
