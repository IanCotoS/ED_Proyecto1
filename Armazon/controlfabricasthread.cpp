
#include "controlfabricasthread.h"

void ControlFabricasThread::mandarAFabricar()
{
    if (!colaParaFabricacion->isEmpty()){
        Pedido pedido = colaParaFabricacion->dequeue();
        NodoArticulo * tmp = pedido.articulos->primerNodo;
        while (tmp != NULL){
            if (!tmp->articulo->estaListo()){
                QString categoria = tmp->articulo->categoria;
                if (categoria == "A"){
                    if (colaFabricaComodin->size() < colaFabricaA->size()){
                        colaFabricaComodin->enqueue((*tmp->articulo));
                    }
                    else{
                        colaFabricaA->enqueue((*tmp->articulo));
                    }
                }
                else if (categoria == "B"){
                    if (colaFabricaComodin->size() < colaFabricaA->size()){
                        colaFabricaComodin->enqueue((*tmp->articulo));
                    }
                    else{
                        colaFabricaB->enqueue((*tmp->articulo));
                    }
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
