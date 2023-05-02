
#include "mainwindow.h"
#include "ui_mainwindow.h"

QString CLIENTE_PNG = "img\\cliente.png";
QString BALANCEADOR_PNG = "img\\balanceador.png";
QString FABRICA_PNG = "img\\fabrica.png";
QString COLADEALISTADORES_PNG = "img\\colaDeAlistadores.png";
QString EMPACADOR_PNG = "img\\alistador.png";
QString FACTURA_PNG = "img\\factura.png";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // # Images
    QPixmap image_cliente1= QPixmap(CLIENTE_PNG).scaled(ui->label_ImagenCliente1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenCliente1->setPixmap(image_cliente1);

    QPixmap image_cliente2= QPixmap(CLIENTE_PNG).scaled(ui->label_ImagenCliente2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenCliente2->setPixmap(image_cliente2);

    QPixmap image_cliente3= QPixmap(CLIENTE_PNG).scaled(ui->label_ImagenCliente3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenCliente3->setPixmap(image_cliente3);

    QPixmap image_balanceador = QPixmap(BALANCEADOR_PNG).scaled(ui->label_ImagenBalanceador->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenBalanceador->setPixmap(image_balanceador);

    QPixmap image_fabricaA= QPixmap(FABRICA_PNG).scaled(ui->label_ImagenFabricaA->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenFabricaA->setPixmap(image_fabricaA);

    QPixmap image_fabricaB= QPixmap(FABRICA_PNG).scaled(ui->label_ImagenFabricaB->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenFabricaB->setPixmap(image_fabricaB);

    QPixmap image_fabricaC= QPixmap(FABRICA_PNG).scaled(ui->label_ImagenFabricaC->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenFabricaC->setPixmap(image_fabricaC);

    QPixmap image_fabricaExtra= QPixmap(FABRICA_PNG).scaled(ui->label_ImagenFabricaExtra->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenFabricaExtra->setPixmap(image_fabricaExtra);

    QPixmap image_colaDeAlistadores= QPixmap(COLADEALISTADORES_PNG).scaled(ui->label_ImagenColaDeAlistadores->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenColaDeAlistadores->setPixmap(image_colaDeAlistadores);

    QPixmap image_empacador= QPixmap(EMPACADOR_PNG).scaled(ui->label_ImagenEmpacador->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenEmpacador->setPixmap(image_empacador);

    QPixmap image_factura= QPixmap(FACTURA_PNG).scaled(ui->label_ImagenFactura->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_ImagenFactura->setPixmap(image_factura);

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
    colaAlistados =new Cola<Pedido>();
    colaFactura= new Cola<Pedido>();

    // Colas (fabrica)
    colaFabricaA = new Cola<NodoArticulo>();
    colaFabricaB = new Cola<NodoArticulo>();
    colaFabricaC = new Cola<NodoArticulo>();
    colaFabricaComodin = new Cola<NodoArticulo>();

    // Threads
    pedidosThread = new PedidosThread("Pedidos Thread", colaPedidosPrioridad, colaPedidosNormales, clientes, articulos);
    pedidosThread->start();

    balanceador = new Balanceador("Balanceador Thread", colaPedidosPrioridad, colaPedidosNormales,
                                  colaAlistos, colaParaFabricar, articulos);
    balanceador->start();

    controlFabricasThread = new ControlFabricasThread("Control Fabricas Thread", colaParaFabricar,
                                                      colaAlistos, colaFabricaA, colaFabricaB,
                                                      colaFabricaC, colaFabricaComodin);
    controlFabricasThread->start();

    fabricaAThread = new FabricasThread("Fabrica A Thread", colaFabricaA);
    fabricaAThread->start();

    fabricaBThread = new FabricasThread("Fabrica B Thread", colaFabricaB);
    fabricaBThread->start();

    fabricaCThread = new FabricasThread("Fabrica C Thread", colaFabricaC);
    fabricaCThread->start();

    fabricaComodinThread = new FabricasThread("Fabrica Comodin Thread", colaFabricaComodin);
    fabricaComodinThread->start();

    colaDeAlistadores= new Alistador("Cola de Alistadores", colaAlistos, colaAlistados);
    colaDeAlistadores->start();

    empacador = new Empacador("Empacador", colaAlistados, colaFactura);
    empacador->start();

    facturacionThread = new FacturacionThread("Facturacion Thread", colaFactura);
    facturacionThread->start();
}


MainWindow::~MainWindow()
{
    Funciones::crearArchivo("ArchivosDeTexto\\Articulos_Actualizados", articulos->devuelveInfo());
    delete ui;
}



void MainWindow::on_pushButton_stopBalanceador_clicked()
{
    balanceador->pause();
}


void MainWindow::on_pushButton_resumeBalanceador_clicked()
{
    balanceador->resume();
}


void MainWindow::on_pushButton_stopFabricaA_clicked()
{
    fabricaAThread->pause();
}


void MainWindow::on_pushButton_resumeFabricaA_clicked()
{
    fabricaAThread->resume();
}


void MainWindow::on_pushButton_stopFabricaB_clicked()
{
    fabricaBThread->pause();
}


void MainWindow::on_pushButton_resumeFabricaB_clicked()
{
    fabricaBThread->resume();
}


void MainWindow::on_pushButton_stopFabricaC_clicked()
{
    fabricaCThread->pause();
}


void MainWindow::on_pushButton_resumeFabricaC_clicked()
{
    fabricaCThread->resume();
}


void MainWindow::on_pushButton_stopEmpacador_clicked()
{
    empacador->pause();
}


void MainWindow::on_pushButton_resumeEmpacador_clicked()
{
    empacador->resume();
}

