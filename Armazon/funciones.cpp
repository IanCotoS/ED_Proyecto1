
#include "funciones.h"

// Funciones
QString Funciones::crearArchivo(QString pNombreArchivo, QString pContenido){
    QFile file(pNombreArchivo);
    QString texto;
    if (!file.open(QIODevice::WriteOnly)){
        texto += file.errorString();
    }
    else{
        QTextStream stream(&file);
        stream << pContenido;
        texto += "Se creó el archivo " + pNombreArchivo + ".";
    }
    file.close();
    return texto;
}

QString Funciones::retornarTextoArchivo(QString pNombreArchivo){
    QFile file(pNombreArchivo);
    QString texto;
    if (!file.exists()){
        texto += "El archivo " + pNombreArchivo + " no existe.";
    }
    else if (!file.open(QIODevice::ReadOnly)){
        texto += file.errorString();
    }
    else{
        QTextStream stream(&file);
        texto = stream.readAll();
    }
    file.close();
    return texto;
}

void Funciones::crearFactura(QString nombre, QString * contenido){
    Funciones::crearArchivo("ArchivosDeTexto\\Facturas\\" + nombre, *contenido);
}

void Funciones::crearArchivoError(QString nombre, QString contenido){
    Funciones::crearArchivo("ArchivosDeTexto\\Pedidos\\Defectuosos\\" + nombre, contenido);
    QFile::remove("ArchivosDeTexto\\Pedidos\\Entrantes\\"  + nombre);
}

QStringList Funciones::devuelveNombresTxtCarpeta(QString pCarpeta){
    QDir directory(pCarpeta);
    return directory.entryList(QStringList() << "*.txt" << "*.TXT", QDir::Files);
}

QStringList Funciones::separaSaltoLinea(QString str){
    // Separa los datos en una lista temporal por \r\n
    static QRegularExpression re("\\r\\n");
    return str.split(re);
}

QStringList Funciones::separaTab(QString str){
    // Separa los datos en una lista temporal por \t
    static QRegularExpression re("\\t");
    return str.split(re);
}

bool Funciones::validarFormato(QString pString, QRegularExpression pExpresionRegular){
    // Valida el formato de la expresión regular contra el string
    QRegularExpressionMatch match = pExpresionRegular.match(pString);
    return match.hasMatch();
}

QString Funciones::obtenerHoraString(){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    return formattedTime;
}
