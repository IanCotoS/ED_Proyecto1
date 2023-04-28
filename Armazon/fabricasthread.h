
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
    FabricasThread(QString id, QString categoria, Cola<Pedido>* colaParaFabricacion, Cola<Pedido>* colaFabrica,
                   QLabel* label, QLabel* attendingLabel){
        running = false;
        this->id = id;
        this->categoria = categoria;
        this->colaParaFabricacion = colaParaFabricacion;
        this->colaFabrica = colaFabrica;
        this->label = label;
        this->attendingLabel = attendingLabel;
    }

    // Métodos Thread
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    // Atributos
    QString id;
    QString categoria  ;
    bool running;
    Cola<Pedido> * colaParaFabricacion;
    Cola<Pedido>* colaFabrica;
    QLabel * label;
    QLabel * attendingLabel;

    // Declaraciones de métodos
    void fabricando();

}; // Fin Clase fabricasThread

#endif // FABRICASTHREAD_H
