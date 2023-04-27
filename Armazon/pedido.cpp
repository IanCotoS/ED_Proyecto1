
#include "pedido.h"

// Pedido
// Constructor
Pedido::Pedido(int pNumero, Cliente* pCliente, ListaArticulos* pArticulos) :
    numero(pNumero), cliente(pCliente), articulos(pArticulos),
    recibo("Pedido: " + QString::number(pNumero) + "\r\nCliente: " + pCliente->codigo){}

// Funciones Pedido
QString Pedido::devuelveInfo(){
    return ("\r\nPedido " + QString::number(numero) + "\r\nCliente: " + cliente->devuelveInfo() +
            "\r\nArtículos: " +  articulos->devuelveInfo() + recibo);
}
