
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Listas
    ListaClientes * clientes = new ListaClientes();
    ListaArticulos * articulos = new ListaArticulos();

    if (!(clientes->cargarEnMemoria() && articulos->cargarEnMemoria())){
        delete clientes;
        delete articulos;
    }

    // Colas
    Cola<Pedido> * colaPedidos = new Cola<Pedido>();
    Cola<Pedido> * colaAlistos = new Cola<Pedido>();

    // QLabels
    QLabel * labelPedidosThread = new QLabel();
    QLabel * attendingLabelPedidosThread = new QLabel();
    QLabel * labelFacturacionThread = new QLabel();
    QLabel * attendingLabelFacturacionThread = new QLabel();

    // Threads
    PedidosThread * pedidosThread = new PedidosThread("Pedidos Thread", colaPedidos, clientes, articulos,
                                                     labelPedidosThread, attendingLabelPedidosThread);
    pedidosThread->run();

    FacturacionThread * facturacionThread = new FacturacionThread("Facturacion Thread", colaAlistos, labelFacturacionThread,
                                                                 attendingLabelFacturacionThread);
    facturacionThread->run();

}


MainWindow::~MainWindow()
{
    delete ui;
}


