
#ifndef ALISTADOR_H
#define ALISTADOR_H
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

class Alistador : public QThread
{
public:
    QString estado;
    Pedido*pedidoAli;
    Pedido*pedidoListo;
    bool listo;

    Alistador(int id){
        running=true;
        this->id=id;
        this->tiempoPedido=0;
        this->matrizMieo={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                            "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U","V", "W", "X", "Y", "Z"};
        estado="Inactivo";
        pedidoAli=nullptr;
        listo=false;
        pedidoListo=nullptr;
    }
    int recorrido(QString ubicacion){
        QString space{" "};
        QString replaceStr=ubicacion[0]+space;
        ubicacion.replace(ubicacion[0], replaceStr);
        QStringList infoUbicacion=ubicacion.split(" ");
        int posicionFila=matrizMieo.indexOf(infoUbicacion.at(0));
        int posicionColumna=infoUbicacion.at(1).toInt();
        return posicionFila+posicionColumna;

    }
    void alistarPedido(){
        Articulo* tmp=NULL;
        pedidoAli->recibo=pedidoAli->recibo+"\nA alisto: "+Funciones::obtenerHoraString();
        for(int y=0;y<pedidoAli->articulos->cantidad;y++) {
            tmp=pedidoAli->articulos->devuelveArticuloPos(y);
            tiempoPedido=tiempoPedido+recorrido(tmp->ubicacionBodega);
        }



    }
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run(){
        while (running==true){
            if (pedidoAli!=nullptr){
                listo=false;
                alistarPedido();
                while (tiempoPedido > 0)
                {
                    QThread::sleep(1);
                    tiempoPedido--;
                }
                listo=true;
                pedidoListo=pedidoAli;
                pedidoAli=nullptr;
            }
            QThread::sleep(1);
        }
    }


private:
    int id;
    int tiempoPedido;
    bool running;
    QStringList matrizMieo;


};

class ColaAlistadores : public QThread
{
public:
    ColaAlistadores(Cola<Pedido>*pedidosPorAlistar, Cola<Pedido>*pedidosListos){
        this->pedidosPorAlistar=pedidosPorAlistar;
        this->pedidosListos=pedidosListos;
        this->colaAlistadores=new Cola<Alistador*>;
        for(int i=1; i<=6;i++){
            colaAlistadores->enqueue(new Alistador(i));
        }
        running=false;
    }
    void run(){
        while (running==true){
            Alistador*alistador1=nullptr;
            Alistador*alistador2=nullptr;
            Alistador*alistador3=nullptr;
            Alistador*alistador4=nullptr;
            Alistador*alistador5=nullptr;
            Alistador*alistador6=nullptr;

            if (!pedidosPorAlistar->isEmpty()){
                while (!pedidosPorAlistar->isEmpty()){
                    Pedido pedidoPorAlistar= pedidosPorAlistar->dequeue();
                    if ((!pedidosPorAlistar->isEmpty()) and (alistador1==nullptr) ){
                        alistador1=colaAlistadores->dequeue();
                        alistador1->estado="Activo";
                        alistador1->pedidoAli=&pedidoPorAlistar;
                        alistador1->run();
                    }
                    else{
                        if ((!pedidosPorAlistar->isEmpty()) and (alistador2==nullptr) ){
                            alistador2=colaAlistadores->dequeue();
                            alistador2->estado="Activo";
                            alistador2->pedidoAli=&pedidoPorAlistar;
                            alistador2->run();
                        }
                        else{
                            if ((!pedidosPorAlistar->isEmpty()) and (alistador3==nullptr) ){
                                alistador3=colaAlistadores->dequeue();
                                alistador3->estado="Activo";
                                alistador3->pedidoAli=&pedidoPorAlistar;
                                alistador3->run();
                            }
                            else{
                                if ((!pedidosPorAlistar->isEmpty()) and (alistador4==nullptr) ){
                                    alistador4=colaAlistadores->dequeue();
                                    alistador4->estado="Activo";
                                    alistador4->pedidoAli=&pedidoPorAlistar;
                                    alistador4->run();
                                }
                                else{
                                    if ((!pedidosPorAlistar->isEmpty()) and (alistador5==nullptr) ){
                                        alistador5=colaAlistadores->dequeue();
                                        alistador5->estado="Activo";
                                        alistador5->pedidoAli=&pedidoPorAlistar;
                                        alistador5->run();
                                    }
                                    else{
                                        if ((!pedidosPorAlistar->isEmpty()) and (alistador6==nullptr) ){
                                            alistador6=colaAlistadores->dequeue();
                                            alistador6->estado="Activo";
                                            alistador6->pedidoAli=&pedidoPorAlistar;
                                            alistador6->run();
                                        }
                                        else{
                                            if((alistador1!=nullptr)&&(alistador1->listo==true)){
                                                pedidosListos->enqueue(*alistador1->pedidoListo);
                                                alistador1->pedidoListo=nullptr;
                                                colaAlistadores->enqueue(alistador1);
                                                alistador1->estado="Inactivo";
                                                alistador1=nullptr;
                                            }
                                            else{
                                                if((alistador2!=nullptr)&&(alistador2->listo==true)){
                                                    pedidosListos->enqueue(*alistador2->pedidoListo);
                                                    alistador2->pedidoListo=nullptr;
                                                    colaAlistadores->enqueue(alistador2);
                                                    alistador2->estado="Inactivo";
                                                    alistador2=nullptr;
                                                }
                                                else{
                                                    if((alistador3!=nullptr)&&(alistador3->listo==true)){
                                                        pedidosListos->enqueue(*alistador3->pedidoListo);
                                                        alistador3->pedidoListo=nullptr;
                                                        colaAlistadores->enqueue(alistador3);
                                                        alistador3->estado="Inactivo";
                                                        alistador3=nullptr;
                                                    }
                                                    else{
                                                        if((alistador4!=nullptr)&&(alistador4->listo==true)){
                                                            pedidosListos->enqueue(*alistador4->pedidoListo);
                                                            alistador4->pedidoListo=nullptr;
                                                            colaAlistadores->enqueue(alistador4);
                                                            alistador4->estado="Inactivo";
                                                            alistador4=nullptr;
                                                        }
                                                        else{
                                                            if((alistador5!=nullptr)&&(alistador5->listo==true)){
                                                                pedidosListos->enqueue(*alistador5->pedidoListo);
                                                                alistador5->pedidoListo=nullptr;
                                                                colaAlistadores->enqueue(alistador5);
                                                                alistador5->estado="Inactivo";
                                                                alistador5=nullptr;
                                                            }
                                                            else{
                                                                if((alistador6!=nullptr)&&(alistador6->listo==true)){
                                                                    pedidosListos->enqueue(*alistador6->pedidoListo);
                                                                    alistador6->pedidoListo=nullptr;
                                                                    colaAlistadores->enqueue(alistador1);
                                                                    alistador6->estado="Inactivo";
                                                                    alistador6=nullptr;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
            else{
                QThread::sleep(1);
            }
        }
    }
private:
    Cola<Pedido>*pedidosPorAlistar;
    Cola<Pedido>*pedidosListos;
    Cola<Alistador*>*colaAlistadores;
    bool running;


};
#endif // ALISTADOR_H
