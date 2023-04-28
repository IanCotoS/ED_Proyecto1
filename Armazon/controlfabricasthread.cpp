
#include "controlfabricasthread.h"

void ControlFabricasThread::mandarAFabricar()
{
    if (!colaParaFabricacion->isEmpty()){
        Pedido pedido = colaParaFabricacion->dequeue();
        NodoArticulo * tmp = pedido.articulos->primerNodo;
        while (tmp != NULL){
            if (!tmp->articulo->estaListo()){
                QString categoria = tmp->articulo->categoria;
                int valor = QRandomGenerator::global()->bounded(3);
                if (valor == 0){
                    colaFabricaComodin->enqueue((*tmp->articulo));
                }
                else if (categoria == "A"){
                    colaFabricaA->enqueue((*tmp->articulo));
                }
                else if (categoria == "B"){
                    colaFabricaB->enqueue((*tmp->articulo));
                }
                else{
                    colaFabricaC->enqueue((*tmp->articulo));
                }

            }
            tmp = tmp->siguiente;
        }
        colaFabricando->enqueue(pedido);
    }
}

void ControlFabricasThread::run()
{
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";
        mandarAFabricar();
        QThread::sleep(1);
    }
}
