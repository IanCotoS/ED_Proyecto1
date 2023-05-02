
#include <QApplication>
#include <QLabel>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInfo() << Funciones::obtenerHoraString();

    MainWindow w;
    w.show();
    return a.exec();
}
