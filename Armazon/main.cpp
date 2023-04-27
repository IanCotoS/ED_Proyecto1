
#include <QApplication>
#include <QLabel>
#include "mainwindow.h"
#include "pedido.h"
#include "pedidosthread.h"
#include "cola.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Listas
    ListaClientes * clientes = new ListaClientes();
    ListaArticulos * articulos = new ListaArticulos();

    if (!(clientes->cargarEnMemoria() && articulos->cargarEnMemoria())){
        delete clientes;
        delete articulos;
        return 0;
    }

    // Colas
    Cola<Pedido> * colaPedidos = new Cola<Pedido>();

    // QLabels
    QLabel * labelPedidosThread = new QLabel();
    QLabel * attendingLabelPedidosThread = new QLabel();

    // Threads
    PedidosThread * pedidosThread = new PedidosThread("Pedidos Thread", colaPedidos, clientes, articulos,
                                                     labelPedidosThread, attendingLabelPedidosThread);
    pedidosThread->run();

    MainWindow w;
    w.show();
    return a.exec();
}
