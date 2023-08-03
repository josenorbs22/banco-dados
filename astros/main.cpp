#include "login.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        QSqlDatabase db=QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("localhost");
        db.setDatabaseName("postgres");
        db.setPassword("jose22");
        db.setUserName("postgres");
        db.setPort(5432);
        if(db.open())
        {
            qDebug() <<"opened" ;
            //db.close();
        }
    } catch(QSqlError error){
        qDebug() << "Erro do BD: " + error.databaseText();
    }

    Login l;
    l.show();

    return a.exec();
}

/*
 * FAZER ISTO ANTES DE ENTREGAR O TRABALHO
 * Executar windeployqt.exe "C:\Users\josen\OneDrive\Documentos\Jose\UFSC\Banco de Dados\Trabalho Final\build-astros-Desktop_Qt_6_5_1_MinGW_64_bit-Release\release\astros.exe"
 * para dar build no projeto com todas as dlls incluidas no .exe
 * */
