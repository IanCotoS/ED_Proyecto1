
#include "controlfabricasthread.h"

void ControlFabricasThread::mandarAFabricar()
{
    if (!colaParaFabricacion->isEmpty()){
        Pedido pedido = colaParaFabricacion->dequeue();
        NodoArticulo * tmp = pedido.articulos->primerNodo;
        pedido.recibo += "\r\nA fabrica:\t" + Funciones::obtenerHoraString() + "\r\nArtículos:";
        while (tmp != NULL){
            if (!tmp->articulo->estaListo()){
                QString categoria = tmp->articulo->categoria;
                if (categoria == "A"){
                    if (colaFabricaComodin->size() < colaFabricaA->size()){
                        pedido.recibo += "\r\nCodigo:\t" + tmp->articulo->codigo + "\tFabricado en Comodin" +
                                         + "\r\n" + QString::number(tmp->articulo->cantidadComparable) + " unidades" +
                                        "\r\nInicio: " + Funciones::obtenerHoraString() +
                                         "\r\nFin en: " + QString::number(tmp->articulo->cantidadComparable
                                         * tmp->articulo->tiempoFabricacionSegundos) + " segundos";
                        colaFabricaComodin->enqueue((*tmp->articulo));
                    }
                    else{
                        pedido.recibo += "\r\nCodigo:\t" + tmp->articulo->codigo + "\tFabricado en A" +
                                         + "\r\n" + QString::number(tmp->articulo->cantidadComparable) + " unidades" +
                                         "\r\nInicio: " + Funciones::obtenerHoraString() +
                                         "\r\nFin en: " + QString::number(tmp->articulo->cantidadComparable
                                         * tmp->articulo->tiempoFabricacionSegundos) + " segundos";
                        colaFabricaA->enqueue((*tmp->articulo));
                    }
                }
                else if (categoria == "B"){
                    if (colaFabricaComodin->size() < colaFabricaA->size()){
                        pedido.recibo += "\r\nCodigo:\t" + tmp->articulo->codigo + "\tFabricado en Comodin" +
                                         + "\r\n" + QString::number(tmp->articulo->cantidadComparable) + " unidades" +
                                         "\r\nInicio: " + Funciones::obtenerHoraString() +
                                         "\r\nFin en: " + QString::number(tmp->articulo->cantidadComparable
                                         * tmp->articulo->tiempoFabricacionSegundos) + " segundos";
                        colaFabricaComodin->enqueue((*tmp->articulo));
                    }
                    else{
                        pedido.recibo += "\r\nCodigo:\t" + tmp->articulo->codigo + "\tFabricado en B" +
                                         + "\r\n" + QString::number(tmp->articulo->cantidadComparable) + " unidades" +
                                         "\r\nInicio: " + Funciones::obtenerHoraString() +
                                         "\r\nFin en: " + QString::number(tmp->articulo->cantidadComparable
                                         * tmp->articulo->tiempoFabricacionSegundos) + " segundos";
                        colaFabricaB->enqueue((*tmp->articulo));
                    }
                }
                else{
                    pedido.recibo += "\r\nCodigo:\t" + tmp->articulo->codigo + "\tFabricado en C" +
                                     + "\r\n" + QString::number(tmp->articulo->cantidadComparable) + " unidades" +
                                     "\r\nInicio: " + Funciones::obtenerHoraString() +
                                     "\r\nFin en: " + QString::number(tmp->articulo->cantidadComparable
                                         * tmp->articulo->tiempoFabricacionSegundos) + " segundos";
                    colaFabricaC->enqueue((*tmp->articulo));
                }
            }
            tmp = tmp->siguiente;
        }
        qInfo() << pedido.devuelveInfo();
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