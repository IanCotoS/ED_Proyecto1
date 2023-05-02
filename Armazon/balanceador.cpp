
#include "balanceador.h"

void Balanceador::evaluaNormales()
{
    if (!colaPedidoNormales->isEmpty())
    {
        qInfo() << "Ejecutando " + id + "...";
        for (int i=0; i<colaPedidoNormales->size();i++){
            qDebug()<<"Tamaño Cola pedido normal:";
            qDebug()<<QString::number(colaPedidoNormales->size());
            Pedido pedidoB= colaPedidoNormales->dequeue();
            qInfo() << pedidoB.devuelveInfo();
            pedidoB.recibo+="\nBalanceador: "+Funciones::obtenerHoraString();
            NodoArticulo * tmp = pedidoB.articulos->primerNodo;
            while (tmp != nullptr) {
                if (tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad>=1){
                    tmp->articulo->cantidadComparable=tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=
                        listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad-tmp->articulo->cantidad;
                    tmp->articulo->cantidadComparable=0;
                }
                tmp = tmp->siguiente;
            }
            if (pedidoB.articulos->estaListo()==true){
                colaAlisto->enqueue(pedidoB);
            }
            else{
                colaFabricando->enqueue(pedidoB);
            }
        }
        qDebug()<<"Tamaño Cola alisto:";
        qDebug()<<QString::number(colaAlisto->size());
        qDebug()<<"Tamaño Cola fabricando:";
        qDebug()<<QString::number(colaFabricando->size());

    }
}

void Balanceador::evaluaPrioridad()
{
    if (!colaPedidoPrioridad->isEmpty())
    {
        qInfo() << "Ejecutando " + id + "...";
        for (int i=0; i<colaPedidoPrioridad->size();i++){
            qDebug()<<"Tamaño Cola pedio prioridad:";
            qDebug()<<QString::number(colaPedidoPrioridad->size());
            Pedido pedidoB= colaPedidoPrioridad->dequeue();
            qInfo() << pedidoB.devuelveInfo();
            pedidoB.recibo+="\nBalanceador: "+Funciones::obtenerHoraString();
            NodoArticulo * tmp = pedidoB.articulos->primerNodo;
            while (tmp != nullptr) {
                if (tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad>=1){
                    tmp->articulo->cantidadComparable=tmp->articulo->cantidadComparable-listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad;
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=0;
                }
                else{
                    listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad=
                        listaInventario->devuelveArticulo(tmp->articulo->codigo)->cantidad-tmp->articulo->cantidad;
                    tmp->articulo->cantidadComparable=0;
                }
                tmp = tmp->siguiente;
            }
            if (pedidoB.articulos->estaListo()==true){
                colaAlisto->enqueue(pedidoB);
            }
            else{
                colaFabricando->enqueue(pedidoB);
            }
        }
        qDebug()<<"Tamaño Cola alisto:";
        qDebug()<<QString::number(colaAlisto->size());
        qDebug()<<"Tamaño Cola fabricando:";
        qDebug()<<QString::number(colaFabricando->size());
    }
}

void Balanceador::run(){
    running = true;
    while (running)
    {
        evaluaPrioridad();
        evaluaNormales();
        QThread::sleep(5);
    }
}
