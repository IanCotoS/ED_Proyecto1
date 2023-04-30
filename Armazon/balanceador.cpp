
#include "balanceador.h"

void Balanceador::evaluaNormales()
{
    if (!colaPedidoNormales->isEmpty())
    {
        for (int i=0; i<colaPedidoNormales->size();i++){
            Pedido pedidoB= colaPedidoNormales->dequeue();
            qInfo() << pedidoB.devuelveInfo();
            pedidoB.recibo+="\nBalanceador: "+Funciones::obtenerHoraString();
            Articulo* tmp=NULL;
            for(int y=0;y<pedidoB.articulos->cantidad;y++) {
                tmp=pedidoB.articulos->devuelveArticuloPos(y);
                if (tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad>=1){
                    tmp->cantidadComparable=tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->codigo)->cantidad=listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad;
                    tmp->cantidadComparable=0;
                }
                if (pedidoB.articulos->estaListo()==true){
                    colaAlisto->enqueue(pedidoB);
                }
                else{
                    colaFabricando->enqueue(pedidoB);
                }
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
            Articulo* tmp=NULL;
            for(int y=0;y<pedidoB.articulos->cantidad;y++) {
                tmp=pedidoB.articulos->devuelveArticuloPos(y);

                if (tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad>=1){
                    tmp->cantidadComparable=tmp->cantidadComparable-listaInventario->devuelveArticulo(tmp->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->codigo)->cantidad=listaInventario->devuelveArticulo(tmp->codigo)->cantidad-tmp->cantidad;
                    tmp->cantidadComparable=0;
                }
                if (pedidoB.articulos->estaListo()==true){
                    colaAlisto->enqueue(pedidoB);
                }
                else{
                    colaFabricando->enqueue(pedidoB);
                }
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
