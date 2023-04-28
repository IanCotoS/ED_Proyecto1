
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Listas
    clientes = new ListaClientes();
    articulos = new ListaArticulos();

    if (!(clientes->cargarEnMemoria() && articulos->cargarEnMemoria())){
        delete ui;
    }

    // Colas
    colaPedidosPrioridad = new Cola<Pedido>();
    colaPedidosNormales = new Cola<Pedido>();
    colaParaFabricar = new Cola<Pedido>();
    colaFabricando = new Cola<Pedido>();
    colaAlistos = new Cola<Pedido>();

    // Colas (fabrica)
    colaFabricaA = new Cola<Articulo>();
    colaFabricaB = new Cola<Articulo>();
    colaFabricaC = new Cola<Articulo>();
    colaFabricaComodin = new Cola<Articulo>();

    // QLabels
    labelPedidosThread = new QLabel();
    attendingLabelPedidosThread = new QLabel();

    labelFabricaAThread = new QLabel();
    attendingLabelFabricaAThread = new QLabel();

    labelFabricaBThread = new QLabel();
    attendingLabelFabricaBThread = new QLabel();

    labelFabricaCThread = new QLabel();
    attendingLabelFabricaCThread = new QLabel();

    labelFabricaComodinThread = new QLabel();
    attendingLabelFabricaComodinThread = new QLabel();

    labelControlFabricasThread = new QLabel();
    attendingLabelControlFabricasThread = new QLabel();

    labelFacturacionThread = new QLabel();
    attendingLabelFacturacionThread = new QLabel();

    // Threads
    pedidosThread = new PedidosThread("Pedidos Thread", colaPedidosPrioridad, colaPedidosNormales, clientes, articulos,
                                                     labelPedidosThread, attendingLabelPedidosThread);
    pedidosThread->start();

    controlFabricasThread = new ControlFabricasThread("Control Fabricas Thread", colaPedidosPrioridad, colaFabricando, colaFabricaA, // Cambiar parametro 2
                                                      colaFabricaB, colaFabricaC, colaFabricaComodin, labelControlFabricasThread,
                                                      attendingLabelControlFabricasThread);
    controlFabricasThread->start();

    fabricaAThread = new FabricasThread("Fabrica A Thread", colaFabricaA, labelFabricaAThread, attendingLabelFabricaAThread);
    fabricaAThread->start();

    fabricaBThread = new FabricasThread("Fabrica B Thread", colaFabricaB, labelFabricaBThread, attendingLabelFabricaBThread);
    fabricaBThread->start();

    fabricaCThread = new FabricasThread("Fabrica C Thread", colaFabricaC, labelFabricaCThread, attendingLabelFabricaCThread);
    fabricaCThread->start();

    fabricaComodinThread = new FabricasThread("Fabrica Comodin Thread", colaFabricaComodin, labelFabricaComodinThread, attendingLabelFabricaComodinThread);
    fabricaComodinThread->start();

    facturacionThread = new FacturacionThread("Facturacion Thread", colaAlistos, labelFacturacionThread,
                                                                 attendingLabelFacturacionThread);
    facturacionThread->start();

}


MainWindow::~MainWindow()
{
    Funciones::crearArchivo("ArchivosDeTexto\\Articulos_Actualizados", articulos->devuelveInfo());
    delete ui;
}


