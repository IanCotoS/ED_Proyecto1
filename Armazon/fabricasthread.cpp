
#include "fabricasthread.h"

void FabricasThread::run(){
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";

        QThread::sleep(1);
    }
}

void FabricasThread::fabricando()
{
    if (!colaParaFabricacion->isEmpty()){
        Pedido pedidoEvaluar = colaParaFabricacion->peek();
        ListaArticulos * listaArticulosEvaluar = pedidoEvaluar.articulos;
        for (int pos = 0; pos < listaArticulosEvaluar->cantidad; pos++){
            Articulo * articuloEvaluar = listaArticulosEvaluar->devuelveArticuloPos(pos);
            if (articuloEvaluar->categoria == categoria){
                int tiempoFabricacion = articuloEvaluar->cantidadComparable * articuloEvaluar->tiempoFabricacionSegundos;
                QThread::sleep(tiempoFabricacion);
            }
        }
    }
}
