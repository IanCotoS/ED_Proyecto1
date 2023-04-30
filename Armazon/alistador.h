
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

    Alistador(int id){
        running=true;
        this->id=id;
        this->tiempoPedido=0;
        this->matrizMieo={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                            "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U","V", "W", "X", "Y", "Z"};
        estado="Inactivo";
        pedidoAli=NULL;
        listo=false;
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
            if (pedidoAli!=NULL){
                listo=false;
                alistarPedido();
                while (tiempoPedido > 0)
                {
                    QThread::sleep(1);
                    tiempoPedido--;
                }
                listo=true;
                pedidoAli=NULL;

            }

        }
    }


private:
    int id;
    int tiempoPedido;
    bool running;
    QStringList matrizMieo;
    bool listo;


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
            if (!pedidosPorAlistar->isEmpty()){
                Pedido pedidoPorAlistar= pedidosPorAlistar->dequeue();
                Alistador*alistador=colaAlistadores->dequeue();
                alistador->estado="Activo";
                alistador->pedidoAli=&pedidoPorAlistar;
                alistador->run();


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
