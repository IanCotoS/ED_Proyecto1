
#include "facturacionthread.h"

// Métodos
void FacturacionThread::realizarFactura(){
    if (!colaAlistos->isEmpty())
    {
        Pedido pedidoListo = colaAlistos->dequeue();
        QString tituloFactura = QString::number(pedidoListo.numero) + "_" + pedidoListo.cliente->codigo + "_" +
                                Funciones::obtenerHoraString();
        pedidoListo.recibo += "\r\nFacturación: " + Funciones::obtenerHoraString();
        Funciones::crearArchivo("ArchivosDeTexto\\Facturas\\" + tituloFactura, pedidoListo.recibo);
    }
}

void FacturacionThread::run(){
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";
        realizarFactura();
        QThread::sleep(1);
    }
}
