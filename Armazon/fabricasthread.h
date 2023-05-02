
#ifndef FABRICASTHREAD_H
#define FABRICASTHREAD_H

// Imports
#include <QtCore>
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <QFile>


#include "articulo.h"
#include "cliente.h"
#include "cola.h"
#include "pedido.h"
#include "funciones.h"

// Clase fabricasThread
class FabricasThread : public QThread
{
public:

    // Constructor
    FabricasThread(QString id, Cola<NodoArticulo>* colaEnFabrica){
        running = false;
        this->id = id;
        this->tiempoEnCola = 0;
        this->colaEnFabrica = colaEnFabrica;
    }

    // Métodos Thread
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    // Atributos
    QString id;
    int tiempoEnCola;
    bool running;
    Cola<NodoArticulo>* colaEnFabrica;

    // Declaraciones de métodos
    void fabricando();

}; // Fin Clase fabricasThread

#endif // FABRICASTHREAD_H
