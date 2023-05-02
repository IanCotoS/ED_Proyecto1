
#include "fabricasthread.h"

void FabricasThread::fabricando()
{
    if (!colaEnFabrica->isEmpty()){
        NodoArticulo articuloFabricando = colaEnFabrica->dequeue();
        int tiempoAFabricar = articuloFabricando.articulo->tiempoFabricacionSegundos * articuloFabricando.articulo->cantidadComparable;
        QThread::sleep(tiempoAFabricar);
        articuloFabricando.articulo->cantidadComparable = 0;
        qInfo() << articuloFabricando.devuelveInfo();
    }
}

void FabricasThread::run(){
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";
        fabricando();
        QThread::sleep(1);
    }
}
