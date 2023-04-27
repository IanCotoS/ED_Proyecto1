
#ifndef FUNCIONES_H
#define FUNCIONES_H

// Imports
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDir>

// Clase Funciones (Solo para eso, funciones básicas)
class Funciones
{
public:
    // Declaración de funciones
    static QString crearArchivo(QString nombreArchivo, QString contenido);
    static QString retornarTextoArchivo(QString nombreArchivo);
    static void crearArchivoError(QString nombre, QString contenido);
    static QStringList devuelveNombresTxtCarpeta(QString pCarpeta);
    static QStringList separaSaltoLinea(QString str);
    static QStringList separaTab(QString str);
    static bool validarFormato(QString strRevisar, QRegularExpression expRegular);
    static QString obtenerHoraString();
};

#endif // FUNCIONES_H
