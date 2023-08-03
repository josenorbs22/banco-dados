#ifndef USUARIO_H
#define USUARIO_H

#include <QDate>
#include <iostream>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

class Usuario {
private:
    int m_id_usuario;
    std::string m_nome_usuario;
    std::string m_email_usuario;
    std::string m_bio_usuario;
    QDate m_data_nasc_usu;
    std::string m_pword_usuario;

public:
    Usuario():m_id_usuario(0), m_nome_usuario(""), m_email_usuario(""), m_bio_usuario(""), m_data_nasc_usu(QDate::currentDate()){}
    ~Usuario(){}

    int getIdUsuario() const{return m_id_usuario;}
    void setIdUsuario(int id_usuario) {m_id_usuario = id_usuario;}
    std::string getNomeUsuario() const {return m_nome_usuario;}
    void setNomeUsuario(std::string nome_usuario) {m_nome_usuario = nome_usuario;}
    std::string getEmailUsuario() const {return m_email_usuario;}
    void setEmailUsuario(std::string email_usuario) {m_email_usuario = email_usuario;}
    std::string getBioUsuario() const {return m_bio_usuario;}
    void setBioUsuario(std::string bio_usuario) {m_bio_usuario = bio_usuario;}
    QDate getDataNascUsu() const{return m_data_nasc_usu;}
    void setDataNascUsu(QDate data_nasc_usu) {m_data_nasc_usu = data_nasc_usu;}
    void setPwordUsuario(std::string pword_usuario) {m_pword_usuario = pword_usuario;}

    bool registerUsuario();
    bool editUsuario();
    bool loginUsuario();
};

#endif // USUARIO_H
