
#include "facturacionthread.h"

// Métodos
void FacturacionThread::realizarFactura(){
    if (!colaFactura->isEmpty())
    {
        qInfo() << "Ejecutando " + id + "...";
        qDebug()<<"Tamaño Cola por Facturar:";
        qDebug()<<QString::number(colaFactura->size());
        Pedido pedidoListo = colaFactura->dequeue();
        QString tituloFactura = QString::number(pedidoListo.numero) + "_" + pedidoListo.cliente->codigo + "_" +
                                Funciones::obtenerHoraString() + ".txt";
        pedidoListo.recibo += "\r\nFacturación: " + Funciones::obtenerHoraString();
        qInfo() << tituloFactura + pedidoListo.recibo;
        QString * reciboInfo = &pedidoListo.recibo;
        tituloFactura.replace(":", ";");
        Funciones::crearFactura(tituloFactura, reciboInfo);
    }
}

void FacturacionThread::run(){
    running = true;
    while (running)
    {
        realizarFactura();
        QThread::sleep(1);
    }
}
