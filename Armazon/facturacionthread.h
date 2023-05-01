
#ifndef FACTURACIONTHREAD_H
#define FACTURACIONTHREAD_H

#include <QtCore>
#include <QDebug>
#include <QLabel>

#include "articulo.h"
#include "cliente.h"
#include "cola.h"
#include "pedido.h"
#include "funciones.h"

// Clase FacturacionThread
class FacturacionThread : public QThread
{
public:

    // Constructor
    FacturacionThread(QString id, Cola<Pedido>* colaAlistos){
        running = false;
        this->id = id;
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

    // Métodos
    void realizarFactura();

}; // Fin Clase PedidosThread

#endif // FACTURACIONTHREAD_H
