
#include "empacador.h"

void Empacador::run(){
    running=true;
    while(running){
        if (!colaParaEmpacar->isEmpty()){
            qInfo() << "Ejecutando " + id + "...";
            qDebug()<<"Tamaño Cola para empacar:";
            qDebug()<<QString::number(colaParaEmpacar->size());
            for (int i=0; i<colaParaEmpacar->size();i++){
                Pedido pedidoEmpacado=colaParaEmpacar->dequeue();
                int cantArticulos=pedidoEmpacado.articulos->cantidad;
                while (cantArticulos>0){
                    QThread::sleep(1);
                    cantArticulos--;
                }
                pedidoEmpacado.recibo += "\r\nEmpacador " + Funciones::obtenerHoraString();
                colaparaFacturar->enqueue(pedidoEmpacado);
            }
            qDebug() << "Tamaño cola para facturar";
            qDebug() << QString::number(colaparaFacturar->size());
        }
         QThread::sleep(1);
    }
}

