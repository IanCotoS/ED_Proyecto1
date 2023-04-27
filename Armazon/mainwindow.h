
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include "pedido.h"
#include "pedidosthread.h"
#include "facturacionthread.h"
#include "cola.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ListaClientes * clientes;
    ListaArticulos * articulos;
    Cola<Pedido> * colaPedidos;
    Cola<Pedido> * colaAlistos;
    QLabel * labelPedidosThread;
    QLabel * attendingLabelPedidosThread;
    QLabel * labelFacturacionThread;
    QLabel * attendingLabelFacturacionThread;
    PedidosThread * pedidosThread;
    FacturacionThread * facturacionThread;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
