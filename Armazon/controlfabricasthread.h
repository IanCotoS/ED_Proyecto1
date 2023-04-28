
#ifndef CONTROLFABRICASTHREAD_H
#define CONTROLFABRICASTHREAD_H

#include <QtCore>
#include <QDebug>
#include <QLabel>

#include "articulo.h"
#include "cliente.h"
#include "cola.h"
#include "pedido.h"
#include "funciones.h"

// Clase ControlFabricasThread
class ControlFabricasThread : public QThread
{
public:

    // Constructor
    ControlFabricasThread(QString id, Cola<Pedido>* colaParaFabricacion, Cola<Pedido>* colaFabricando,
                          Cola<Articulo>* colaFabricaA, Cola<Articulo>* colaFabricaB,
                          Cola<Articulo>* colaFabricaC, Cola<Articulo>* colaFabricaComodin,
                          QLabel* label, QLabel* attendingLabel){
        running = false;
        this->id = id;
        this->colaParaFabricacion = colaParaFabricacion;
        this->colaFabricando = colaFabricando;
        this->colaFabricaA = colaFabricaA;
        this->colaFabricaB = colaFabricaB;
        this->colaFabricaC = colaFabricaC;
        this->colaFabricaComodin = colaFabricaComodin;
        this->label = label;
        this->attendingLabel = attendingLabel;
    }

    // Métodos Thread
    bool resume() { return running = true; };
    bool pause() { return running = false; };
    void run();

private:
    // Atributos
    QString id;
    bool running;
    Cola<Pedido> * colaParaFabricacion;
    Cola<Pedido>* colaFabricando;
    Cola<Articulo>* colaFabricaA;
    Cola<Articulo>* colaFabricaB;
    Cola<Articulo>* colaFabricaC;
    Cola<Articulo>* colaFabricaComodin;
    QLabel * label;
    QLabel * attendingLabel;

    // Declaraciones de métodos
    void mandarAFabricar();

}; // Fin Clase ControlFabricasThread

#endif // CONTROLFABRICASTHREAD_H
