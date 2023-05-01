
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include "pedido.h"
#include "pedidosthread.h"
#include "facturacionthread.h"
#include "cola.h"
#include "fabricasthread.h"
#include "controlfabricasthread.h"
#include "balanceador.h"
#include "alistador.h"
#include "empacador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Listas
    ListaClientes * clientes;
    ListaArticulos * articulos;

    // Colas de pedidos
    Cola<Pedido> * colaPedidosPrioridad;
    Cola<Pedido> * colaPedidosNormales;
    Cola<Pedido> * colaParaFabricar;
    Cola<Pedido> * colaFabricando;
    Cola<Pedido> * colaAlistos;
    Cola<Pedido> * colaAlistados;
    Cola<Pedido> * colaFactura;

    // Colas de artículos (Fabrica)
    Cola<Articulo> * colaFabricaA;
    Cola<Articulo> * colaFabricaB;
    Cola<Articulo> * colaFabricaC;
    Cola<Articulo> * colaFabricaComodin;

    // Threads
    PedidosThread * pedidosThread;
    Balanceador * balanceador;
    ControlFabricasThread * controlFabricasThread;
    FabricasThread * fabricaAThread;
    FabricasThread * fabricaBThread;
    FabricasThread * fabricaCThread;
    FabricasThread * fabricaComodinThread;
    ColaAlistadores* colaDeAlistadores;
    Empacador * empacador;
    FacturacionThread * facturacionThread;

private slots:
    void on_pushButton_stopBalanceador_clicked();

    void on_pushButton_resumeBalanceador_clicked();

    void on_pushButton_stopFabricaA_clicked();

    void on_pushButton_resumeFabricaA_clicked();

    void on_pushButton_stopFabricaB_clicked();

    void on_pushButton_resumeFabricaB_clicked();

    void on_pushButton_stopFabricaC_clicked();

    void on_pushButton_resumeFabricaC_clicked();

    void on_pushButton_stopEmpacador_clicked();

    void on_pushButton_resumeEmpacador_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
