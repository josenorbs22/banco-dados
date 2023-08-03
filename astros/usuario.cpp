#include "usuario.h"

bool Usuario::registerUsuario(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Usuario (nome_usuario,"
                      " email_usuario,"
                      " bio_usuario,"
                      " data_nasc_usu,"
                      " pword_usuario)"
                      " VALUES (:nome, :email, :bio, :data, :pword)");
        query.bindValue(":nome", QString::fromStdString(this->m_nome_usuario));
        query.bindValue(":email", QString::fromStdString(this->m_email_usuario));
        query.bindValue(":bio", QString::fromStdString(this->m_bio_usuario));
        query.bindValue(":data", this->m_data_nasc_usu);
        query.bindValue(":pword", QString::fromStdString(this->m_pword_usuario));
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}
bool Usuario::editUsuario(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Usuario SET nome_usuario = :nome,"
                      " email_usuario = :email,"
                      " bio_usuario = :bio,"
                      " data_nasc_usu = :data,"
                      " pword_usuario = :pword)"
                      " WHERE id_usuario = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_nome_usuario));
        query.bindValue(":email", QString::fromStdString(this->m_email_usuario));
        query.bindValue(":bio", QString::fromStdString(this->m_bio_usuario));
        query.bindValue(":data", this->m_data_nasc_usu);
        query.bindValue(":pword", QString::fromStdString(this->m_pword_usuario));
        query.bindValue(":id", this->m_id_usuario);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}
bool Usuario::loginUsuario(){
    QSqlQuery query;
    bool done{false};
    try{
        query.prepare("SELECT id_usuario, nome_usuario, bio_usuario, data_nasc_usu FROM astros.Usuario"
                        " WHERE email_usuario = :email AND pword_usuario = :pword");
        query.bindValue(":email", QString::fromStdString(this->m_email_usuario));
        query.bindValue(":pword", QString::fromStdString(this->m_pword_usuario));
        done = query.exec();
        done = (query.size() == 1 ? true : false);
        while(query.next()){
            this->setIdUsuario(query.value(0).toInt());
            this->setNomeUsuario(QString(query.value(1).toString()).toStdString());
            this->setBioUsuario(query.value(2).toString().toStdString());
            this->setDataNascUsu(query.value(3).toDate());
        }
        return done;
    } catch (QSqlError error){
        qDebug() << "Erro de login: " + error.databaseText();
        return false;
    }
}
