
#include "alistador.h"

//Funciones Alistador

int Alistador::recorrido(QString ubicacion){
    QString space{" "};
    QString replaceStr=ubicacion[0]+space;
    ubicacion.replace(ubicacion[0], replaceStr);
    QStringList infoUbicacion=ubicacion.split(" ");
    int posicionFila=matrizMieo.indexOf(infoUbicacion.at(0));
    int posicionColumna=infoUbicacion.at(1).toInt();
    return posicionFila+posicionColumna;
}

void Alistador::alistarPedido(Pedido nPedido){
    NodoArticulo * tmp = nPedido.articulos->primerNodo;
    nPedido.recibo+=nPedido.recibo+"\nA alisto: "+Funciones::obtenerHoraString();
    while(tmp!=nullptr){
        tiempoPedido=tiempoPedido+recorrido(tmp->articulo->ubicacionBodega);
        tmp=tmp->siguiente;
    }
}
void Alistador::run(){
    while (running==true){
        if (!pedidoAli->isEmpty()){
            qInfo() << "Ejecutando " + id + "...";
            qDebug()<<"Tamaño Cola por alistar:";
            qDebug()<<QString::number(pedidoAli->size());
            for (int i =0; i<pedidoAli->size();i++){
                Pedido nPedido=pedidoAli->dequeue();
                listo=false;
                alistarPedido(nPedido);
                while (tiempoPedido > 0)
                {
                    QThread::sleep(1);
                    tiempoPedido--;
                }
                pedidoListo->enqueue(nPedido);
            }
            qDebug()<<"Tamaño Cola pedio Listo:";
            qDebug()<<QString::number(pedidoListo->size());
        }
        QThread::sleep(3);
    }
}
//Funciones Cola Alistadores
