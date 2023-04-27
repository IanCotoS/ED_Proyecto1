
#ifndef CLIENTE_H
#define CLIENTE_H

// Imports
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include "funciones.h"

// Cliente
class Cliente {
public:
    // Constructores
    Cliente(QString codigo, QString nombre, int prioridad);

    // Declaración de métodos
    QString devuelveInfo();

    // Atributos
    QString codigo;
    QString nombre;
    int prioridad;
}; // Fin Cliente

// NodoCliente
class NodoCliente {
public:
    // Constructores
    NodoCliente();
    NodoCliente(Cliente* pCliente);
    NodoCliente(QString pCodigo, QString pNombre, int pPrioridad);

    // Declaración de métodos
    QString devuelveInfo();

    // Atributos
    Cliente* cliente;
    NodoCliente* siguiente;

}; // Fin NodoCliente

// ListaClientes
class ListaClientes {
public:
    // Constructor
    ListaClientes() : primerNodo(nullptr) , cantidad(0){}

    // Declaración de métodos
    void insertarAlFinal(Cliente*);
    void limpiarMemoria();
    QString devuelveInfo();
    Cliente * devuelveCliente(QString) const;
    bool validarDatos(QString, QString);
    bool cargarEnMemoria();

    // Atributos
    NodoCliente * primerNodo;
    int cantidad;

}; // Fin ListaClientes


#endif // CLIENTE_H
