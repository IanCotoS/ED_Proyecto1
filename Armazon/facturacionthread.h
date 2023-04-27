
#ifndef FACTURACIONTHREAD_H
#define FACTURACIONTHREAD_H

#include <QtCore>
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QThread>
#include "articulo.h"
#include "cliente.h"
#include "cola.h"
#include "pedido.h"
#include "funciones.h"

// Clase FacturacionThread
class FacturacionThread : QThread
{
public:

    // Constructor
    FacturacionThread(QString id, Cola<Pedido>* colaAlistos, QLabel* label, QLabel* attendingLabel){
        running = false;
        this->id = id;
        this->label = label;
        this->attendingLabel = attendingLabel;
        this->colaAlistos = colaAlistos;
    }

    // Métodos Thread
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    // Atributos
    QString id;
    bool running;
    Cola<Pedido> * colaAlistos;
    QLabel * label;
    QLabel * attendingLabel;

    // Métodos
    void realizarFactura();

}; // Fin Clase PedidosThread

#endif // FACTURACIONTHREAD_H
