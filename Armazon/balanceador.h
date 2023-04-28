
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
    Balanceador(QList<Pedido>*colaPedido, Cola<Pedido>*colaAlisto, Cola<Pedido>*colaFabricando,
                ListaArticulos*listaInventario, QLabel* label, QLabel* attendingLabel){
        running=false;
        this->colaPedido=colaPedido;
        this->colaAlisto=colaAlisto;
        this->colaFabricando=colaFabricando;
        this->listaInventario=listaInventario;
        this->label=label;
        this->attendingLabel=attendingLabel;
    }
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run(){
        running = true;
        while (running)
        {
            if (!colaPedido->isEmpty())
            {
                for (int i=0; i<colaPedido->size();i++){
                    Pedido pedidoB= colaPedido->at(i);
                    if (pedidoB.cliente->prioridad==10){
                        Articulo* tmp=NULL;
                        for(int y=0;y<pedidoB.articulos->cantidad;y++) {
                            tmp=pedidoB.articulos->devuelveArticuloPos(y);

                            if (tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad>=1){
                                tmp->cantidadComparable=tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad;
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=0;
                            }
                            else{
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad;
                                tmp->cantidadComparable=0;
                            }
                            if (pedidoB.articulos->estaListo()==true){
                                colaAlisto->enqueue(pedidoB);
                                colaPedido->removeAt(i);
                            }
                            else{
                                colaFabricando->enqueue(pedidoB);
                                colaPedido->removeAt(i);
                            }

                        }
                    }
                }
                for (int i=0; i<colaPedido->size();i++){
                    Pedido pedidoB= colaPedido->at(i);
                    if (pedidoB.cliente->prioridad!=10){
                        Articulo* tmp=NULL;
                        for(int y=0;y<pedidoB.articulos->cantidad;y++) {
                            tmp=pedidoB.articulos->devuelveArticuloPos(y);

                            if (tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad>=1){
                                tmp->cantidadComparable=tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad;
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=0;
                            }
                            else{
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad;
                                tmp->cantidadComparable=0;
                            }
                            if (pedidoB.articulos->estaListo()==true){
                                colaAlisto->enqueue(pedidoB);
                                colaPedido->removeAt(i);
                            }
                            else{
                                colaFabricando->enqueue(pedidoB);
                                colaPedido->removeAt(i);
                            }

                        }
                    }
                }
            }

            QThread::sleep(1);
        }
    }



private:
    bool running;
    QList<Pedido>*colaPedido;
    Cola<Pedido>*colaAlisto;
    Cola<Pedido>*colaFabricando;
    ListaArticulos* listaInventario;
    QLabel* label;
    QLabel* attendingLabel;
};

#endif // BALANCEADOR_H
