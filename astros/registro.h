#ifndef REGISTRO_H
#define REGISTRO_H

#include <QMainWindow>
#include "usuario.h"
#include "login.h"

namespace Ui {
class Registro;
}

class Registro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr);
    ~Registro();

private slots:
    void on_senhaUsuario_textChanged(const QString &arg1);

    void on_nomeUsuario_textChanged(const QString &arg1);

    void on_emailUsuario_textChanged(const QString &arg1);

    void on_conSenhaUsuario_textChanged(const QString &arg1);

    void on_registerButton_clicked();

    void on_voltar_clicked();

private:
    Ui::Registro *ui;
};

#endif // REGISTRO_H
