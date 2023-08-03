#include "publicacao.h"
#include "ui_publicacao.h"

//Publicacao::Publicacao(QWidget *parent) :
//    QStackedWidget(parent),
//    ui(new Ui::Publicacao)
//{
//    ui->setupUi(this);
//}

Publicacao::~Publicacao()
{
    //delete ui;
}

bool Publicacao::SavePublicacao(){
    QSqlQuery query, query_avists;
    bool done{false};
    try{
        query.prepare("INSERT INTO astros.Publicacao (desc_publi,"
                      " data_publi,"
                      " is_public)"
                      " VALUES (:desc, :data, :public)");
        query.bindValue(":desc", QString::fromStdString(this->m_desc_publi));
        query.bindValue(":data", this->m_data_publi);
        query.bindValue(":public", this->m_is_public);
        done = query.exec();

        QVariantList ids_avists;
        QVariantList ids_publis;
        for(size_t i = 0; i < this->m_v_avists.size(); i++){
            ids_avists << this->m_v_avists.at(i)->getIdAvistamento();
            ids_publis << query.lastInsertId();
        }
        query_avists.prepare("UPDATE astros.Avistamento SET id_publi = :id_p WHERE id_avistamento = :id");
        query_avists.bindValue(":id_p", ids_publis);
        query_avists.bindValue(":id", ids_avists);
        done = query_avists.execBatch();

        return done;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Publicacao::EditPublicacao(){
    QSqlQuery query, query_avists;
    bool done{false};
    try{
        query.prepare("UPDATE astros.Publicacao SET desc_publi = :desc,"
                      " data_publi = :data,"
                      " is_public = :public"
                      " WHERE id_publi = :id");
        query.bindValue(":desc", QString::fromStdString(this->m_desc_publi));
        query.bindValue(":data", this->m_data_publi);
        query.bindValue(":public", this->m_is_public);
        query.bindValue(":id", this->m_id_publi);
        done = query.exec();

        query_avists.prepare("UPDATE astros.Avistamento SET id_publi = NULL WHERE id_publi = :id_p");
        query_avists.bindValue(":id_p", this->m_id_publi);
        done = query_avists.exec();
        query_avists.clear();
        QVariantList ids_avists;
        for(size_t i = 0; i < this->m_v_avists.size(); i++)
            ids_avists << this->m_v_avists.at(i)->getIdAvistamento();
        query_avists.prepare("UPDATE astros.Avistamento SET id_publi = :id_p WHERE id_avistamento = :id");
        query_avists.bindValue(":id_p", ids_avists);
        query_avists.bindValue(":id", this->m_id_publi);
        done = query_avists.execBatch();
        return done;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Publicacao::DeletePublicacao(){
    QSqlQuery query, query_avists;
    bool done{false};
    try {
        query_avists.prepare("UPDATE astros.Avistamento SET id_publi = NULL WHERE id_publi = :id");
        query_avists.bindValue(":id", this->m_id_publi);
        done = query_avists.exec();
        query.prepare("DELETE FROM astros.Publicacao WHERE id_publi = :id");
        query.bindValue(":id", this->m_id_publi);
        done = query.exec();
        return done;
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
}

void LoadPublicacoes(std::vector<Publicacao> &v_publis, std::vector<Local*> &v_locais){
    v_publis.clear();
    vector<Avistamento*> m_v_avists;
    QSqlQuery query, query_avists, query_usuario;
    query.prepare("SELECT id_publi, desc_publi, data_publi, is_public FROM astros.Publicacao WHERE is_public");
    query.exec();

    while(query.next()){
        Publicacao publi;
        publi.setIdPubli(query.value(0).toInt());
        publi.setDescPubli(query.value(1).toString().toStdString());
        publi.setDataPubli(query.value(2).toDateTime());
        publi.setIsPublic(query.value(3).toBool());

        v_publis.push_back(publi);
    }

    for(size_t i = 0; i < v_publis.size(); i++){

        query_avists.clear();
        query_avists.prepare("SELECT id_avistamento, id_usuario, id_local, data_avist FROM astros.Avistamento WHERE id_publi = :id");
        query_avists.bindValue(":id", v_publis.at(i).getIdPubli());
        query_avists.exec();
        m_v_avists.clear();
        while(query_avists.next()){
            Avistamento *avist = new Avistamento();
            avist->setIdAvistamento(query_avists.value(0).toInt());
            query_usuario.clear();
            query_usuario.prepare("SELECT id_usuario, nome_usuario FROM astros.Usuario WHERE id_usuario = :id_usu");
            query_usuario.bindValue(":id_usu", query_avists.value(1).toInt());
            query_usuario.exec();
            while(query_usuario.next()){
                Usuario *usu = new Usuario();
                usu->setIdUsuario(query_usuario.value(0).toInt());
                usu->setNomeUsuario(query_usuario.value(1).toString().toStdString());
                avist->setUsuario(usu);
            }
            avist->setLocal(FindLocal(query_avists.value(2).toInt(), v_locais));
            avist->setDataAvist(query_avists.value(3).toDateTime());
            m_v_avists.push_back(avist);
        }
        v_publis.at(i).setAvistamentos(m_v_avists);
    }
}
