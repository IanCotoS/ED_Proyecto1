
#ifndef PEDIDOSTHREAD_H
#define PEDIDOSTHREAD_H

// Imports
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

// Clase PedidosThread
class PedidosThread : QThread
{
public:

    // Constructor
    PedidosThread(QString id, Cola<Pedido>* colaPedidos, ListaClientes * clientes,
                  ListaArticulos * articulos, QLabel* label, QLabel* attendingLabel){
        running = false;
        this->id = id;
        this->label = label;
        this->attendingLabel = attendingLabel;
        this->colaPedidos = colaPedidos;
        this->clientes = clientes;
        this->articulos = articulos;
    }

    // Métodos Thread
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    // Atributos
    QString id;
    bool running;
    Cola<Pedido> * colaPedidos;
    ListaArticulos * articulos;
    ListaClientes * clientes;
    QLabel * label;
    QLabel * attendingLabel;

    // Declaraciones de métodos
    bool validaDatos(QStringList lineas, QString str, QString nombre);
    ListaArticulos * procesarArticulos(QStringList lineas, QString str, QString nombre);
    void cargarEnMemoria();

}; // Fin Clase PedidosThread

#endif // PEDIDOSTHREAD_H