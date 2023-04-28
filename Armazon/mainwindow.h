
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

    // Colas de artículos (Fabrica)
    Cola<Articulo> * colaFabricaA;
    Cola<Articulo> * colaFabricaB;
    Cola<Articulo> * colaFabricaC;
    Cola<Articulo> * colaFabricaComodin;

    // Labels
    QLabel * labelPedidosThread;
    QLabel * attendingLabelPedidosThread;

    QLabel * labelFabricaAThread;
    QLabel * attendingLabelFabricaAThread;

    QLabel * labelFabricaBThread;
    QLabel * attendingLabelFabricaBThread;

    QLabel * labelFabricaCThread;
    QLabel * attendingLabelFabricaCThread;

    QLabel * labelFabricaComodinThread;
    QLabel * attendingLabelFabricaComodinThread;

    QLabel * labelControlFabricasThread;
    QLabel * attendingLabelControlFabricasThread;

    QLabel * labelFacturacionThread;
    QLabel * attendingLabelFacturacionThread;

    // Threads
    PedidosThread * pedidosThread;
    ControlFabricasThread * controlFabricasThread;
    FabricasThread * fabricaAThread;
    FabricasThread * fabricaBThread;
    FabricasThread * fabricaCThread;
    FabricasThread * fabricaComodinThread;
    FacturacionThread * facturacionThread;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
