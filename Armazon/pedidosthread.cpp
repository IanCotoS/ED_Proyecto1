
#include "pedidosthread.h"

// Variables
// Expresiones regulares
QRegularExpression reNumero("^[1-9]\\d*$");

// Métodos
bool PedidosThread::validaDatos(QStringList lineas, QString str, QString nombre){
    if (lineas.length() < 3){
        str += "\r\nDebe haber al menos 3 líneas, un número de pedido, un código de cliente y un pedido.";
        Funciones::crearArchivoError(nombre, str);
        return false;
    }
    QString numPedido = lineas[0];
    QString codigoCliente = lineas[1];
    if (!Funciones::validarFormato(numPedido, reNumero)){
        str += "\r\nEl número " + numPedido + " debe ser mayor a 0.";
        Funciones::crearArchivoError(nombre, str);
        return false;
    }
    Cliente * clienteNew = clientes->devuelveCliente(codigoCliente);
    if (clienteNew == NULL){
        str += "\r\nEl código " + codigoCliente + " no se encontró en la lista de clientes.";
        Funciones::crearArchivoError(nombre, str);
        return false;
    }
    return true;
}

ListaArticulos * PedidosThread::procesarArticulos(QStringList lineas, QString str, QString nombre){
    ListaArticulos * articulosPedidos = new ListaArticulos();
    for (int i = 2; i < lineas.length(); i++){
        QStringList objArticulos = Funciones::separaTab(lineas[i]);
        if (objArticulos.length() != 2){
            str += "\r\nDebe haber un código de artículo y una cantidad. Error línea " + QString::number(i+1);
            articulosPedidos->limpiarMemoria();
            Funciones::crearArchivoError(nombre, str);
            return nullptr;
        }
        QString codigo = objArticulos[0];
        QString cantidad = objArticulos[1];
        Articulo * articuloNew = articulos->devuelveArticulo(codigo);
        if (!Funciones::validarFormato(cantidad, reNumero)){
            str += "\r\nLa cantidad " + cantidad + " debe ser mayor a 0.";
            articulosPedidos->limpiarMemoria();
            Funciones::crearArchivoError(nombre, str);
            return nullptr;
        }
        if (articuloNew == NULL){
            str += "\r\nEl código " + codigo + " no se encontró en la lista de artículos.";
            articulosPedidos->limpiarMemoria();
            Funciones::crearArchivoError(nombre, str);
            return nullptr;
        }
        articulosPedidos->insertarAlFinal(new Articulo(articuloNew->codigo, cantidad.toInt(),
                                                       articuloNew->tiempoFabricacionSegundos,
                                                       articuloNew->categoria, articuloNew->ubicacionBodega));
    }
    return articulosPedidos;
}

void PedidosThread::cargarEnMemoria(){
    const QString direccionEntrantes = "ArchivosDeTexto\\Pedidos\\Entrantes\\";
    QStringList nombresPedidos = Funciones::devuelveNombresTxtCarpeta(direccionEntrantes);
    if (!nombresPedidos.empty()){
        for (int num = 0; num < nombresPedidos.size(); num++){
            const QString nombre = nombresPedidos[num];
            QString str = Funciones::retornarTextoArchivo(direccionEntrantes + nombre);
            QStringList lineas = Funciones::separaSaltoLinea(str);
            if (validaDatos(lineas, str, nombre)){
                Cliente * clienteNew = clientes->devuelveCliente(lineas[1]);
                ListaArticulos * articulosPedidos = procesarArticulos(lineas, str, nombre);
                if (articulosPedidos != nullptr){
                    Pedido newPedido = Pedido(lineas[0].toInt(),
                                              new Cliente(clienteNew->codigo, clienteNew->nombre, clienteNew->prioridad),
                                              articulosPedidos);
                    newPedido.recibo += "\r\nEn cola:\t" + Funciones::obtenerHoraString();
                    if (clienteNew->prioridad == 10){
                        colaPedidosPrioridad->enqueue(newPedido);
                    }
                    else{
                        colaPedidosNormales->enqueue(newPedido);
                    }
                    QFile::remove(direccionEntrantes + nombre);
                }
            }
        }
    }
}

void PedidosThread::run(){
    running = true;
    while (running)
    {
        qInfo() << "Ejecutando " + id + "...";
        cargarEnMemoria();
        QThread::sleep(5);
    }
}
