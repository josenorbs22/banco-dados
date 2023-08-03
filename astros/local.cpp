#include "local.h"
#include "ui_local.h"

//Local::Local(QWidget *parent) :
//    QFrame(parent),
//    ui(new Ui::Local)
//{
//    ui->setupUi(this);
//}

Local::~Local()
{
    //delete ui;
}

bool Local::SaveLocal(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Local (cidade,"
                      " estado_prov,"
                      " pais,"
                      " latitude,"
                      " longitude)"
                      " VALUES (:cidade, :estado, :pais, :latitude, :longitude)");
        query.bindValue(":cidade", QString::fromStdString(this->m_cidade));
        query.bindValue(":estado", QString::fromStdString(this->m_estado));
        query.bindValue(":pais", QString::fromStdString(this->m_pais));
        query.bindValue(":latitude", QString::fromStdString(this->m_latitude));
        query.bindValue(":longitude", QString::fromStdString(this->m_longitude));
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Local::EditLocal(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Local SET cidade = :cidade,"
                      " estado_prov = :estado,"
                      " pais = :pais,"
                      " latitude = :latitude,"
                      " longitude = :longitude"
                      " WHERE id_local = :id");
        query.bindValue(":cidade", QString::fromStdString(this->m_cidade));
        query.bindValue(":estado", QString::fromStdString(this->m_estado));
        query.bindValue(":pais", QString::fromStdString(this->m_pais));
        query.bindValue(":latitude", QString::fromStdString(this->m_latitude));
        query.bindValue(":longitude", QString::fromStdString(this->m_longitude));
        query.bindValue(":id", this->m_id_local);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Local::DeleteLocal(){
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Local WHERE id_local = :id");
        query.bindValue(":id", this->m_id_local);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
}

void LoadLocais(std::vector<Local*> &v_locais){
    v_locais.clear();
    QSqlQuery query("SELECT id_local, cidade, estado_prov, pais, latitude, longitude FROM astros.Local");

    while(query.next()){
        Local *local = new Local();
        local->setIdLocal(query.value(0).toInt());
        local->setCidade(query.value(1).toString().toStdString());
        local->setEstado(query.value(2).toString().toStdString());
        local->setPais(query.value(3).toString().toStdString());
        local->setLatitude(query.value(4).toString().toStdString());
        local->setLongitude(query.value(5).toString().toStdString());

        v_locais.push_back(local);
    }
}

Local* FindLocal(size_t idLocal, const std::vector<Local*> &v_locais){
    for(size_t i = 0; i < v_locais.size(); i++){
        if(idLocal == v_locais.at(i)->getIdLocal()){
            Local *local = v_locais.at(i);
            return local;
        }
    }
    return NULL;
}
