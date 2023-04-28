
#include "fabricasthread.h"

void FabricasThread::fabricando()
{
    if (!colaEnFabrica->isEmpty()){
        Articulo articuloFabricando = colaEnFabrica->dequeue();
        int tiempoAFabricar = articuloFabricando.tiempoFabricacionSegundos * articuloFabricando.cantidadComparable;
        QThread::sleep(tiempoAFabricar);
        articuloFabricando.cantidadComparable = 0;
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
