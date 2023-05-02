
#ifndef EMPACADOR_H
#define EMPACADOR_H
#include <QString>
#include <QStringList>
#include <QtCore>
#include <QDebug>
#include <QLabel>
#include <QList>
#include"cola.h"
#include"pedido.h"
#include"articulo.h"
#include"funciones.h"



class Empacador : public QThread
{
public:
    Empacador(QString id, Cola<Pedido> * colaParaEmpacar, Cola<Pedido> * colaParaFacturar){
        running=false;
        this->id=id;
        this->colaParaEmpacar=colaParaEmpacar;
        this->colaparaFacturar=colaParaFacturar;
    }
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();
private:
    bool running;
    QString id;
    Cola<Pedido> * colaParaEmpacar;
    Cola<Pedido> * colaparaFacturar;
};

#endif // EMPACADOR_H
