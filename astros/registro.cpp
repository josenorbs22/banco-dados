#include "registro.h"
#include "ui_registro.h"

Registro::Registro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);
}

Registro::~Registro()
{
    delete ui;
}

void Registro::on_senhaUsuario_textChanged(const QString &arg1)
{
    if(ui->senhaUsuario->text().size() > 0 && QString::compare(ui->senhaUsuario->text(), ui->conSenhaUsuario->text(), Qt::CaseSensitive) && ui->nomeUsuario->text().size() > 0 && ui->emailUsuario->text().size() > 0){
        ui->registerButton->setEnabled(true);
    }
}


void Registro::on_nomeUsuario_textChanged(const QString &arg1)
{
    if(ui->senhaUsuario->text().size() > 0 && QString::compare(ui->senhaUsuario->text(), ui->conSenhaUsuario->text(), Qt::CaseSensitive) && ui->nomeUsuario->text().size() > 0 && ui->emailUsuario->text().size() > 0){
        ui->registerButton->setEnabled(true);
    }
}


void Registro::on_emailUsuario_textChanged(const QString &arg1)
{
    if(ui->senhaUsuario->text().size() > 0 && QString::compare(ui->senhaUsuario->text(), ui->conSenhaUsuario->text(), Qt::CaseSensitive) && ui->nomeUsuario->text().size() > 0 && ui->emailUsuario->text().size() > 0){
        ui->registerButton->setEnabled(true);
    }
}


void Registro::on_conSenhaUsuario_textChanged(const QString &arg1)
{
    if(ui->conSenhaUsuario->text().size() > 0 && QString::compare(ui->senhaUsuario->text(), ui->conSenhaUsuario->text(), Qt::CaseSensitive) && ui->nomeUsuario->text().size() > 0 && ui->emailUsuario->text().size() > 0){
        ui->registerButton->setEnabled(true);
    }
}


void Registro::on_registerButton_clicked()
{
    Usuario usuario;
    usuario.setNomeUsuario(ui->nomeUsuario->text().toStdString());
    usuario.setEmailUsuario(ui->emailUsuario->text().toStdString());
    usuario.setBioUsuario(ui->bioUsuario->toPlainText().toStdString());
    usuario.setDataNascUsu(ui->dataNasc->date());
    if(ui->senhaUsuario->text().toStdString() == ui->conSenhaUsuario->text().toStdString())
        usuario.setPwordUsuario(ui->senhaUsuario->text().toStdString());
    if(usuario.registerUsuario()){
        Login *login = new Login();
        login->show();
        this->close();
    }
}


void Registro::on_voltar_clicked()
{
    Login *login = new Login();
    login->show();
    this->close();
}

