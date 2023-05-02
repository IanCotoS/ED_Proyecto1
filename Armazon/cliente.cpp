
#include "cliente.h"

// Variables
// Expresiones regulares
QRegularExpression reCodigoCliente("^\\d{3}$");
QRegularExpression rePrioridad("^([1-9]|10){1}$");

// Funciones Clientes
// Constructor
Cliente::Cliente(QString pCodigo, QString pNombre, int pPrioridad)
    : codigo(pCodigo), nombre(pNombre), prioridad(pPrioridad) {}

QString Cliente::devuelveInfo(){
    return "\r\nCodigo\t" + codigo + "\r\nNombre\t" + nombre +
           "\r\nPrioridad\t" + QString::number(prioridad);
}

// Funciones NodoCliente
// Constructores
NodoCliente::NodoCliente() : cliente(nullptr), siguiente(nullptr) {}

NodoCliente::NodoCliente(Cliente* pCliente) : cliente(pCliente), siguiente(nullptr) {}

NodoCliente::NodoCliente(QString pCodigo, QString pNombre, int pPrioridad)
    : cliente(new Cliente(pCodigo, pNombre, pPrioridad)), siguiente(nullptr) {}

// Funciones NodoCliente
QString NodoCliente::devuelveInfo(){
    return cliente->devuelveInfo();
}

// Funciones ListaCliente
void ListaClientes::insertarAlFinal(Cliente * pCliente){
    if (primerNodo == NULL){
        primerNodo = new NodoCliente(pCliente);
    }
    else{
        NodoCliente * tmp = primerNodo;
        while(tmp->siguiente != NULL){
            tmp = tmp->siguiente;
        }
        NodoCliente * nuevo = new NodoCliente(pCliente);
        tmp->siguiente = nuevo;
    }
    cantidad++;
}

void ListaClientes::limpiarMemoria(){
    NodoCliente * tmp = primerNodo;
    NodoCliente * sig;
    while (tmp != NULL) {
        sig = tmp->siguiente;
        delete tmp;
        tmp = sig;
    }
    primerNodo = NULL;
    delete this; // Se elimina en memoria todo
}

QString ListaClientes::devuelveInfo(){
    NodoCliente * tmp = primerNodo;
    QString info = "";
    while(tmp != NULL){
        info += tmp->devuelveInfo();
        tmp = tmp->siguiente;
    }
    return (info + "\r\n");
}

Cliente * ListaClientes::devuelveCliente(QString pCodigo) const{
    NodoCliente * tmp = primerNodo;
    while(tmp != NULL){
        if (tmp->cliente->codigo == pCodigo){
            return tmp->cliente;
        }
        tmp = tmp->siguiente;
    }
    return NULL;
}

bool ListaClientes::validarDatos(QString pCodigo, QString pPrioridad){
    if (!Funciones::validarFormato(pCodigo, reCodigoCliente)){
        qCritical() << "El código del cliente " + pCodigo + " cuenta con un formato incorrecto.";
                           return false;
    }
    else if (!Funciones::validarFormato(pPrioridad, rePrioridad)){
        qCritical() << "La prioridad de los clientes debe ser un número entre 1 y 10 (" <<
            pPrioridad << ")";
        return false;
    }
    return true;
}

bool ListaClientes::cargarEnMemoria() {
    const QString nomArchivo = "ArchivosDeTexto\\Clientes.txt";
    QString str = Funciones::retornarTextoArchivo(nomArchivo);
    QStringList lineas = Funciones::separaSaltoLinea(str);
    const int camposEsperados = 3;
    for (int i = 0; i < lineas.length(); ++i) {
        const QStringList campos = Funciones::separaTab(lineas[i]);
        if (campos.length() != camposEsperados) {
            qCritical() << "La línea" << i + 1 << "en" << nomArchivo << "no tiene" << camposEsperados << "campos";
                limpiarMemoria(); // En caso de error, libera memoria y retorna false
            return false;
        }
        const QString codigo = campos[0]; // Para hacerlo más legible
        const QString nombre = campos[1];
        const QString prioridadStr = campos[2];
        if (!validarDatos(codigo, prioridadStr)) {
            qCritical() << "Error en la línea" << i + 1 << "en el archivo de los clientes";
                limpiarMemoria();
            return false;
        }
        if (devuelveCliente(codigo) != nullptr) {
            qCritical() << "El código" << codigo << "ya se encuentra en la lista de clientes.";
                limpiarMemoria();
            return false;
        }
        insertarAlFinal(new Cliente(codigo, nombre, prioridadStr.toInt()));
    }
    return true;
}

