
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
                          Cola<NodoArticulo>* colaFabricaA, Cola<NodoArticulo>* colaFabricaB,
                          Cola<NodoArticulo>* colaFabricaC, Cola<NodoArticulo>* colaFabricaComodin){
        running = false;
        this->id = id;
        this->colaParaFabricacion = colaParaFabricacion;
        this->colaFabricando = colaFabricando;
        this->colaFabricaA = colaFabricaA;
        this->colaFabricaB = colaFabricaB;
        this->colaFabricaC = colaFabricaC;
        this->colaFabricaComodin = colaFabricaComodin;
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
    Cola<NodoArticulo>* colaFabricaA;
    Cola<NodoArticulo>* colaFabricaB;
    Cola<NodoArticulo>* colaFabricaC;
    Cola<NodoArticulo>* colaFabricaComodin;

    // Declaraciones de métodos
    void mandarAFabricar();

}; // Fin Clase ControlFabricasThread

#endif // CONTROLFABRICASTHREAD_H
