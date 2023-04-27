
#ifndef PEDIDO_H
#define PEDIDO_H

// Imports
#include "articulo.h"
#include "cliente.h"

// Clase Pedido
class Pedido {
public:

    // Constructor
    Pedido(int pNumero, Cliente* pCliente, ListaArticulos* pArticulos);

    // Declaraciones de métodos
    QString devuelveInfo();

    // Atributos
    int numero;
    Cliente* cliente;
    ListaArticulos* articulos;

}; // Fin Pedido

#endif // PEDIDO_H
