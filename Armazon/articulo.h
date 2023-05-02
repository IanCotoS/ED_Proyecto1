
#ifndef ARTICULO_H
#define ARTICULO_H

// Imports
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>
#include "funciones.h"

// Clase Articulo
class Articulo{
public:
    // Constructor
    Articulo(QString pCodigo, int pCantidad, int pTiempoFabricacionSegundos,
             QString pCategoria, QString pUbicacionBodega);

    // Atributos
    QString codigo;
    int cantidad;
    int tiempoFabricacionSegundos;
    QString categoria;
    QString ubicacionBodega;
    int cantidadComparable;

    // Encabezado de métodos
    bool estaListo();
    QString devuelveInfo();
};

// Clase NodoArticulo
class NodoArticulo{
public:
    // Constructores
    NodoArticulo();
    NodoArticulo(Articulo *pArticulo);
    NodoArticulo(QString pCodigo, int pCantidad, int pTiempoFabricacion,
                 QString pCategoria, QString pUbicacionBodega);

    // Atributos
    Articulo *articulo;
    NodoArticulo *siguiente;
    NodoArticulo *anterior;

    // Encabezado de métodos
    QString devuelveInfo();
};

// Clase ListaArticulos
class ListaArticulos{
public:
    // Constructor
    ListaArticulos();

    // Atributos
    NodoArticulo *primerNodo;
    NodoArticulo *ultimoNodo;
    int cantidad;

    // Encabezado de métodos
    void insertarAlFinal(Articulo *articulo);
    bool estaListo();
    QString devuelveInfo();
    Articulo * devuelveArticuloPos(int pos);
    Articulo * devuelveArticulo(QString codigo);
    void limpiarMemoria();
    bool validarDatos(QString codigo, QString cantidad, QString tiempo, QString categoria, QString ubicacion);
    bool cargarEnMemoria();
};

#endif // ARTICULO_H
