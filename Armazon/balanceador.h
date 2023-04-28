
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
    Balanceador(QList<Pedido>*colaPedido, Cola<Pedido>*colaAlisto, Cola<Pedido>*colaFabricaA,
    Cola<Pedido>*colaFabricaB, Cola<Pedido>*colaFabricaC, Cola<Pedido>*colaFabricaComodin,
                ListaArticulos*listaInventario, QLabel* label, QLabel* attendingLabel){
        running=false;
        this->colaPedido=colaPedido;
        this->colaAlisto=colaAlisto;
        this->colaFabricaA=colaFabricaA;
        this->colaFabricaB=colaFabricaB;
        this->colaFabricaC=colaFabricaC;
        this->colaFabricaComodin=colaFabricaComodin;
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
                        QList<QString> listaFaltantes;
                        bool faltaA=false;
                        bool faltaB=false;
                        bool faltaC=false;
                        for(int y=0;y<pedidoB.articulos->cantidad;y++) {
                            tmp=pedidoB.articulos->devuelveArticuloPos(y);

                            if (listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad<0){
                                listaFaltantes.append(tmp->codigo);
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=0;
                            }
                            else{
                                listaInventario->devuelveArticulo(tmp->codigo)->cantidad=listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad;
                            }
                            if (listaFaltantes.empty()==true){
                                colaAlisto->enqueue(pedidoB);
                                colaPedido->removeAt(i);
                            }
                            else{
                                for(int x=0;x<listaFaltantes.size();x++){
                                    if (listaInventario->devuelveArticulo(listaFaltantes.at(x))->categoria=="A"){
                                        faltaA=true;
                                    }
                                    else{
                                        if()
                                    }
                                }
                            }

                        }
                    }
                }





S





                Pedido*  = queue->dequeue();
                label->setText(queue->_toString());

                while (waitTime > 0)
                {
                    attendingLabel->setText(QString::number(waitTime--));
                    QThread::sleep(1);
                }
            }

            QThread::sleep(1);
        }
    }



private:
    bool running;
    QList<Pedido>*colaPedido;
    Cola<Pedido>*colaAlisto;
    Cola<Pedido>*colaFabricaA;
    Cola<Pedido>*colaFabricaB;
    Cola<Pedido>*colaFabricaC;
    Cola<Pedido>*colaFabricaComodin;
    ListaArticulos* listaInventario;
    QLabel* label;
    QLabel* attendingLabel;
};

#endif // BALANCEADOR_H
