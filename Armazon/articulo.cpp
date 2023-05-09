
#include "articulo.h"

// Variables
// Expresiones regulares
QRegularExpression reCodigoArticulo("^[A-Z]\\d{2}$");
QRegularExpression reCantidad("^\\d+$");
QRegularExpression reTiempoFabricacionSeg("^([1-9]\\d+|[1-9])$");
QRegularExpression reCategoria("^(A|B|C)$");
QRegularExpression reUbicacionBodega("^[A-Z](0[1-9]|10){1}$");

// Objeto
// Constructor
Articulo::Articulo(QString pCodigo, int pCantidad, int pTiempoFabricacionSegundos,
                   QString pCategoria, QString pUbicacionBodega): codigo(pCodigo),
    cantidad(pCantidad), tiempoFabricacionSegundos(pTiempoFabricacionSegundos),
    categoria(pCategoria), ubicacionBodega(pUbicacionBodega), cantidadComparable(pCantidad){}

// Métodos Articulo
bool Articulo::estaListo(){
    return cantidadComparable == 0;
}

QString Articulo::devuelveInfo(){
    return ("\r\nCodigo " + codigo + "\r\nCantidad en almacen: " + QString::number(cantidad) +
            "\r\nTiempo de fabricacion (segundos): " + QString::number(tiempoFabricacionSegundos) +
            "\r\nCategoria: " + categoria + "\r\nUbicacion: " + ubicacionBodega +
            "\r\nCantidad real: " + QString::number(cantidadComparable));
}

// Nodo
// Constructor
NodoArticulo::NodoArticulo() : articulo(nullptr), siguiente(nullptr), anterior(nullptr){}
NodoArticulo::NodoArticulo(Articulo * pArticulo) : articulo(pArticulo), siguiente(nullptr), anterior(nullptr){}
NodoArticulo::NodoArticulo(QString pCodigo, int pCantidad, int pTiempoFabricacion,
                           QString pCategoria, QString pUbicacionBodega) : articulo(new Articulo(pCodigo, pCantidad,
                            pTiempoFabricacion, pCategoria, pUbicacionBodega)), siguiente(nullptr), anterior(nullptr){}

// Métodos NodoArticulo
QString NodoArticulo::devuelveInfo(){
    return (articulo->devuelveInfo());
}

// Lista
// Consturctor
ListaArticulos::ListaArticulos() : primerNodo(nullptr), ultimoNodo(nullptr), cantidad(0){}

// Métodos ListaArticulos
void ListaArticulos::insertarAlFinal(Articulo * pArticulo){
    if (primerNodo == NULL){
        primerNodo = new NodoArticulo(pArticulo);
        ultimoNodo = primerNodo;
    }
    else{
        NodoArticulo *nuevo = new NodoArticulo(pArticulo);
        ultimoNodo->siguiente = nuevo;
        nuevo->anterior = ultimoNodo;
        ultimoNodo = nuevo;
    }
    cantidad++;
}

bool ListaArticulos::estaListo(){
    NodoArticulo * temp = primerNodo;
    while (temp!=NULL){
        if (!temp->articulo->estaListo())
            return false;
        temp = temp->siguiente;
    }
    return true;
}

QString ListaArticulos::devuelveInfo(){
    NodoArticulo * tmp = primerNodo;
    QString info = "";
    while(tmp != NULL){
        info += tmp->devuelveInfo();
        tmp = tmp->siguiente;
    }
    delete tmp;
    return (info + "\r\n");
}

Articulo * ListaArticulos::devuelveArticuloPos(int pos){
    int i = 0;
    NodoArticulo * temp = primerNodo;
    while (temp!=NULL){
        if (pos == i)
            return temp->articulo;
        temp = temp->siguiente;
    }
    return NULL;
}

Articulo * ListaArticulos::devuelveArticulo(QString pCodigo){
    NodoArticulo * tmp = primerNodo;
    while(tmp != NULL){
        if (tmp->articulo->codigo == pCodigo){
            return tmp->articulo;
        }
        tmp = tmp->siguiente;
    }
    return NULL;
}

void ListaArticulos::limpiarMemoria(){
    NodoArticulo * tmp = primerNodo;
    NodoArticulo * sig;
    while (tmp != NULL) {
        sig = tmp->siguiente;
        delete tmp;
        tmp = sig;
    }
    primerNodo = NULL;
    delete this; // Se elimina en memoria todo
}

bool ListaArticulos::validarDatos(QString pCodigo, QString pCantidad, QString pTiempoFabricacionSegundos,
                                  QString pCategoria, QString pUbicacionBodega){
    if (!Funciones::validarFormato(pCodigo, reCodigoArticulo)){
        qCritical() << "El código del artículo " + pCodigo + " cuenta con un formato incorrecto.";
        return false;
    }
    else if(!Funciones::validarFormato(pCantidad, reCantidad)){
        qCritical() << "La cantidad en almacén debe ser 0 o mayor (" << pCantidad << ").";
            return false;
    }
    else if (!Funciones::validarFormato(pTiempoFabricacionSegundos, reTiempoFabricacionSeg)){
        qCritical() << "El tiempo de fabricación debe ser mayor a 0 (" << pTiempoFabricacionSegundos << ").";
            return false;
    }
    else if (!Funciones::validarFormato(pCategoria, reCategoria)){
        qCritical() << "La categoria debe ser A, B o C (" << pCategoria << ").";
        return false;
    }
    else if (!Funciones::validarFormato(pUbicacionBodega, reUbicacionBodega)){
        qCritical() << "La ubicación en bodega debe ser una letra mayúscula," <<
                       "seguido de un número del 01 al 10 (" << pUbicacionBodega << ").";
            return false;
    }
    return true;
}

bool ListaArticulos::cargarEnMemoria(){
    const QString nomArchivo = "ArchivosDeTexto\\Articulos.txt";
    QString str = Funciones::retornarTextoArchivo(nomArchivo);
    QStringList lineas = Funciones::separaSaltoLinea(str);
    const int camposEsperados = 5;
    for (int numLinea = 0; numLinea < lineas.length(); numLinea++){
        QStringList objArticulo = Funciones::separaTab(lineas[numLinea]);
        if (objArticulo.length() != camposEsperados){
            qCritical() << "La línea" << numLinea + 1 << "en" << nomArchivo << "no tiene" << camposEsperados << "campos";
                limpiarMemoria(); // En caso de error, libera memoria y retorna false
            return false;
        }
        const QString codigo = objArticulo[0];
        const QString cantidad = objArticulo[1];
        const QString tiempo = objArticulo[2];
        const QString categoria = objArticulo[3];
        const QString ubicacion = objArticulo[4];
        if (!validarDatos(codigo, cantidad, tiempo, categoria, ubicacion)){
            qCritical() << "Error en la línea" << numLinea+1 << "en el archivo de los artículos";
            limpiarMemoria();
            return false;
        }
        if (devuelveArticulo(codigo) != NULL){
            qCritical() << "El código del artículo " + codigo + " ya se encuentra en la lista de artículos.";
            limpiarMemoria();
            return false;
        }
        this->insertarAlFinal(new Articulo(codigo, cantidad.toInt(), tiempo.toInt(), categoria, ubicacion));
    }
    qDebug() << this->devuelveInfo();
    return true;
}
