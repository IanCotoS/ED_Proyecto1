
#include "balanceador.h"

void Balanceador::evaluaNormales()
{
    if (!colaPedidoNormales->isEmpty())
    {
        for (int i=0; i<colaPedidoNormales->size();i++){
            Pedido pedidoB= colaPedidoNormales->dequeue();
            qInfo() << pedidoB.devuelveInfo();
            pedidoB.recibo+="\nBalanceador: "+Funciones::obtenerHoraString();
            NodoArticulo * tmp = pedidoB.articulos->primerNodo;
            for(int y=0;y<pedidoB.articulos->cantidad;y++) {

                if (tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad>=1){
                    tmp->articulo->cantidadComparable=tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=
                        listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad-tmp->articulo->cantidad;
                    tmp->articulo->cantidadComparable=0;
                }
                if (pedidoB.articulos->estaListo()==true){
                    colaAlisto->enqueue(pedidoB);
                }
                else{
                    colaFabricando->enqueue(pedidoB);
                }
                tmp = tmp->siguiente;
            }
        }
    }
}

void Balanceador::evaluaPrioridad()
{
    if (!colaPedidoPrioridad->isEmpty())
    {
        for (int i=0; i<colaPedidoPrioridad->size();i++){
            Pedido pedidoB= colaPedidoPrioridad->dequeue();
            qInfo() << pedidoB.devuelveInfo();
            pedidoB.recibo+="\nBalanceador: "+Funciones::obtenerHoraString();
            NodoArticulo * tmp = pedidoB.articulos->primerNodo;
            for(int y=0;y<pedidoB.articulos->cantidad;y++) {

                if (tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad>=1){
                    tmp->articulo->cantidadComparable=tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=
                        listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad-tmp->articulo->cantidad;
                    tmp->articulo->cantidadComparable=0;
                }
                if (pedidoB.articulos->estaListo()==true){
                    colaAlisto->enqueue(pedidoB);
                }
                else{
                    colaFabricando->enqueue(pedidoB);
                }
                tmp = tmp->siguiente;
            }
        }
    }
}

void Balanceador::run(){
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";
        evaluaPrioridad();
        evaluaNormales();
        QThread::sleep(5);
    }
}
