
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
    bool listo;

    Alistador(QString id, Cola<Pedido>* pedidoAli,Cola<Pedido>* pedidoListo){
        running=true;
        this->id=id;
        this->tiempoPedido=0;
        this->matrizMieo={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                            "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U","V", "W", "X", "Y", "Z"};
        estado="Inactivo";
        this->pedidoAli=pedidoAli;
        listo=false;
        this->pedidoListo=pedidoListo;
    }
    int recorrido(QString ubicacion);

    void alistarPedido(Pedido nPedido);

    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();


private:
    QString id;
    int tiempoPedido;
    bool running;
    QStringList matrizMieo;
    Cola<Pedido>*pedidoAli;
    Cola <Pedido>*pedidoListo;


};
#endif // ALISTADOR_H
