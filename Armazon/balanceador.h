
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
                                        if(listaInventario->devuelveArticulo(listaFaltantes.at(x))->categoria=="B"){
                                            faltaB=true;
                                        }
                                        else{
                                            if (listaInventario->devuelveArticulo(listaFaltantes.at(x))->categoria=="C"){
                                                faltaC=true;
                                            }
                                        }
                                    }
                                }
                                if(faltaA==true){
                                    if(colaFabricaA->size()<=colaFabricaComodin->size()){
                                        colaFabricaA->enqueue(pedidoB);
                                    }else{
                                        colaFabricaComodin->enqueue(pedidoB);
                                    }
                                }
                                else{
                                    if (faltaB==true){
                                        if(colaFabricaB->size()<=colaFabricaComodin->size()){
                                            colaFabricaB->enqueue(pedidoB);
                                        }else{
                                            colaFabricaComodin->enqueue(pedidoB);
                                        }
                                    }
                                    else{
                                        if(faltaC==true){
                                            colaFabricaC->enqueue(pedidoB);
                                        }
                                    }
                                }
                                colaPedido->removeAt(i);
                            }

                        }
                    }
                    else{
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
                                        if(listaInventario->devuelveArticulo(listaFaltantes.at(x))->categoria=="B"){
                                            faltaB=true;
                                        }
                                        else{
                                            if (listaInventario->devuelveArticulo(listaFaltantes.at(x))->categoria=="C"){
                                                faltaC=true;
                                            }
                                        }
                                    }
                                }
                                if(faltaA==true){
                                    if(colaFabricaA->size()<=colaFabricaComodin->size()){
                                        colaFabricaA->enqueue(pedidoB);
                                    }else{
                                        colaFabricaComodin->enqueue(pedidoB);
                                    }
                                }
                                else{
                                    if (faltaB==true){
                                        if(colaFabricaB->size()<=colaFabricaComodin->size()){
                                            colaFabricaB->enqueue(pedidoB);
                                        }else{
                                            colaFabricaComodin->enqueue(pedidoB);
                                        }
                                    }
                                    else{
                                        if(faltaC==true){
                                            colaFabricaC->enqueue(pedidoB);
                                        }
                                    }
                                }
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
    Cola<Pedido>*colaFabricaA;
    Cola<Pedido>*colaFabricaB;
    Cola<Pedido>*colaFabricaC;
    Cola<Pedido>*colaFabricaComodin;
    ListaArticulos* listaInventario;
    QLabel* label;
    QLabel* attendingLabel;
};

#endif // BALANCEADOR_H
