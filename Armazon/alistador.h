
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
    int recorrido(QString ubicacion);

    void alistarPedido();

    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();


private:
    int id;
    int tiempoPedido;
    bool running;
    QStringList matrizMieo;


};

class ColaAlistadores : public QThread
{
public:
    ColaAlistadores(QString id, Cola<Pedido>*pedidosPorAlistar, Cola<Pedido>*pedidosListos){
        this->id=id;
        this->pedidosPorAlistar=pedidosPorAlistar;
        this->pedidosListos=pedidosListos;
        this->colaAlistadores=new Cola<Alistador*>;
        for(int i=1; i<=6;i++){
            colaAlistadores->enqueue(new Alistador(i));
        }
        running=false;
    }
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    QString id;
    Cola<Pedido>*pedidosPorAlistar;
    Cola<Pedido>*pedidosListos;
    Cola<Alistador*>*colaAlistadores;
    bool running;


};
#endif // ALISTADOR_H
