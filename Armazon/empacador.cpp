
#include "empacador.h"

void Empacador::run(){
    running=true;
    while(running){
        if (!colaParaEmpacar->isEmpty()){
            Pedido pedidoEmpacado=colaParaEmpacar->dequeue();
            int cantArticulos=pedidoEmpacado.articulos->cantidad;
            while (cantArticulos>0){
                QThread::sleep(1);
                cantArticulos--;
            }
            colaparaFacturar->enqueue(pedidoEmpacado);
        }
         QThread::sleep(1);
    }
}

