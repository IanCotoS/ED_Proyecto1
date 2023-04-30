
#ifndef BALANCEADOR_H
#define BALANCEADOR_H
#include <QtCore>
#include <QDebug>
#include <QLabel>
#include <QList>
#include"cola.h"
#include"pedido.h"
#include"articulo.h"


class Balanceador: public QThread
{
public:
    Balanceador(QString id, Cola<Pedido>* colaPedidoPrioridad, Cola<Pedido>*colaPedidoNormales, Cola<Pedido>*colaAlisto, Cola<Pedido>*colaFabricando,
                ListaArticulos*listaInventario, QLabel* label, QLabel* attendingLabel){
        running=false;
        this->id=id;
        this->colaPedidoPrioridad=colaPedidoPrioridad;
        this->colaPedidoNormales=colaPedidoNormales;
        this->colaAlisto=colaAlisto;
        this->colaFabricando=colaFabricando;
        this->listaInventario=listaInventario;
        this->label=label;
        this->attendingLabel=attendingLabel;
    }

    void evaluaPrioridad();
    void evaluaNormales();

    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    QString id;
    bool running;
    Cola<Pedido>*colaPedidoPrioridad;
    Cola<Pedido>*colaPedidoNormales;
    Cola<Pedido>*colaAlisto;
    Cola<Pedido>*colaFabricando;
    ListaArticulos* listaInventario;
    QLabel* label;
    QLabel* attendingLabel;
};

#endif // BALANCEADOR_H
