
#include "pedido.h"

// Pedido
// Constructor
Pedido::Pedido(int pNumero, Cliente* pCliente, ListaArticulos* pArticulos) :
    numero(pNumero), cliente(pCliente), articulos(pArticulos),
    recibo("Pedido: " + QString::number(pNumero) + "\r\nCliente: " + pCliente->codigo){}

// Funciones Pedido
QString Pedido::devuelveInfo(){
    return (QString::number(numero) + " " + cliente->devuelveInfo() + " " + articulos->devuelveInfo());
}
