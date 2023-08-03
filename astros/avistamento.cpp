#include "avistamento.h"

Avistamento::~Avistamento(){

}

bool Avistamento::saveAvistamento(){
    QSqlQuery query_avist;
    QSqlQuery query_astros;
    QSqlQuery query_equip;
    QSqlQuery query_imagem;
    try{
        query_avist.prepare("INSERT INTO astros.Avistamento (id_usuario,"
                      " id_local,"
                      " data_avist)"
                      " VALUES (:usuario, :local, :data)");
        query_avist.bindValue(":usuario", this->m_usuario->getIdUsuario());
        query_avist.bindValue(":local", this->m_local->getIdLocal());
        query_avist.bindValue(":data", this->m_data_avist);
        query_avist.exec();
        QVariantList astros;
        QVariantList ids_avist_a;
        for(size_t i = 0; i < this->m_v_astros.size(); i++){
            astros << this->m_v_astros.at(i)->GetId();
            ids_avist_a << query_avist.lastInsertId();
        }
        QVariantList equips;
        QVariantList ids_avist_e;
        for(size_t i = 0; i < this->m_v_equips.size(); i++){
            equips << this->m_v_equips.at(i)->getIdEquip();
            ids_avist_e << query_avist.lastInsertId();
        }
        QVariantList desc_imagem;
        QVariantList tamanhos_imagem;
        QVariantList ids_avist_i;
        for(size_t i = 0; i < this->m_v_imagens.size(); i++){
            desc_imagem << QString::fromStdString(this->m_v_imagens.at(i).getDescImagem());
            tamanhos_imagem << this->m_v_imagens.at(i).getTamanhoImagem();
            ids_avist_i << query_avist.lastInsertId();
        }
        query_astros.prepare("INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (:astro, :avistamento)");
        query_astros.bindValue(":astro", astros);
        query_astros.bindValue(":avistamento", ids_avist_a);
        query_equip.prepare("INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (:equip, :avistamento)");
        query_equip.bindValue(":equip", equips);
        query_equip.bindValue(":avistamento", ids_avist_e);
        for(size_t i = 0; i < this->m_v_imagens.size(); i++){
            query_imagem.clear();
            query_imagem.prepare("INSERT INTO astros.Imagem (desc_imagem, id_avistamento) VALUES (:desc, :id_avist)");
            query_imagem.bindValue(":desc", QString::fromStdString(this->m_v_imagens.at(i).getDescImagem()));
            query_imagem.bindValue(":id_avist", query_avist.lastInsertId());
            query_imagem.exec();
            this->m_v_imagens.at(i).setIdImagem(query_imagem.lastInsertId().toInt());
            this->m_v_imagens.at(i).getImgFile().save("./avistamentos/" + this->m_v_imagens.at(i).getIdImagem(), "PNG", 10);
        }

        query_astros.execBatch();
        query_equip.execBatch();

        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Avistamento::editAvistamento(vector<Astro*> &v_astros, vector<Equipamento*> &v_equips){
    QSqlQuery query_avist;
//    QSqlQuery query_astros;
//    QSqlQuery query_equip;
//    QSqlQuery query_imagem;
    try{
        query_avist.prepare("UPDATE astros.Avistamento SET "
                            " id_local = :local"
                            " WHERE id_avistamento = :id");
        query_avist.bindValue(":local", this->m_local->getIdLocal());
        query_avist.bindValue(":id", this->m_id_avistamento);
        query_avist.exec();
//        while(query_avist.next()){
//            QVariantList astros;
//            for(size_t i = 0; i < v_astros.size(); i++)
//                astros << v_astros.at(i).GetId();
//            QVariantList equips;
//            for(size_t i = 0; i < v_equips.size(); i++)
//                equips << v_equips.at(i).getIdEquip();
//            QVariantList desc_imagem;
//            QVariantList tamanhos_imagem;
//            for(size_t i = 0; i < this->m_v_imagens.size(); i++){
//                desc_imagem << QString::fromStdString(this->m_v_imagens.at(i)->getDescImagem());
//                tamanhos_imagem << this->m_v_imagens.at(i)->getTamanhoImagem();
//            }
//            query_astros.prepare("INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (:astro, :avistamento)");
//            query_astros.bindValue(":astro", astros);
//            query_astros.bindValue(":avistamento", query_avist.value(0));
//            query_equip.prepare("INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (:equip, :avistamento)");
//            query_equip.bindValue(":equip", equips);
//            query_equip.bindValue(":avistamento", query_avist.value(0));
//            query_imagem.prepare("INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento) VALUES (:desc, :tamanho, :id_avist)");
//            query_imagem.bindValue(":desc", desc_imagem);
//            query_imagem.bindValue(":tamanho", tamanhos_imagem);
//            query_imagem.bindValue(":avistamento", query_avist.value(0));
//            query_astros.execBatch();
//            query_equip.execBatch();
//            query_imagem.execBatch();
//        }
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Avistamento::deleteAvistamento(){
    QSqlQuery query_avist, query_imagem, query_astro, query_equip;
    try {
        query_imagem.prepare("DELETE FROM astros.Imagem WHERE id_avistamento = :id");
        query_astro.prepare("DELETE FROM astros.Avist_astro WHERE id_avistamento = :id");
        query_equip.prepare("DELETE FROM astros.Equip_avist WHERE id_avistamento = :id");
        query_avist.prepare("DELETE FROM astros.Avistamento WHERE id_avistamento = :id");
        query_imagem.bindValue(":id", this->m_id_avistamento);
        query_astro.bindValue(":id", this->m_id_avistamento);
        query_equip.bindValue(":id", this->m_id_avistamento);
        query_avist.bindValue(":id", this->m_id_avistamento);
        query_imagem.exec();
        query_astro.exec();
        query_equip.exec();
        return query_avist.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
}





void loadAvistamentos(vector<Avistamento*> &v_avists, Usuario *usuario, vector<Local*> &v_locais){
    v_avists.clear();
    vector<Imagem> v_imagens;
    vector<Equipamento*> v_equips;
    vector<Astro*> v_astros;
    QSqlQuery query, query_imagem, query_equips, query_astros;
    query.prepare("SELECT id_avistamento, id_usuario, id_local, id_publi, data_avist FROM astros.Avistamento WHERE id_usuario = :id_usuario");
    query.bindValue(":id_usuario", usuario->getIdUsuario());
    query.exec();



    while(query.next()){
        Local *local = FindLocal(query.value(2).toInt(), v_locais);
        Avistamento *avistamento = new Avistamento();
        avistamento->setIdAvistamento(query.value(0).toInt());
        avistamento->setLocal(local);
        avistamento->setDataAvist(query.value(4).toDateTime());
        avistamento->setIdP(query.value(3).toInt());
        v_avists.push_back(avistamento);
    }

    for(size_t i = 0; i < v_avists.size(); i++){
//        query_local.clear();
//        query_local.prepare("SELECT id_local, cidade, estado, pais, latitude, longitude FROM astros.Local WHERE id_local = :id_local");
//        query_local.bindValue(":id_local", v_avists.at(i)->getLocal()->getIdLocal());
//        query_local.exec();

//        while(query_local.next()){
//            local.setIdLocal(query_local.value(0).toInt());
//            local.setCidade(query_local.value(1).toString().toStdString());
//            local.setEstado(query_local.value(2).toString().toStdString());
//            local.setPais(query_local.value(3).toString().toStdString());
//            local.setLatitude(query_local.value(4).toString().toStdString());
//            local.setLongitude(query_local.value(5).toString().toStdString());
//        }
//        v_avists.at(i)->setLocal(&local);

        query_imagem.clear();
        query_imagem.prepare("SELECT id_imagem, desc_imagem, tamanho_imagem FROM astros.Imagem WHERE id_avistamento = :id");
        query_imagem.bindValue(":id", v_avists.at(i)->getIdAvistamento());
        query_imagem.exec();
        v_imagens.clear();
        while(query_imagem.next()){
            Imagem imagem;
            QPixmap qImg;
            imagem.setIdImagem(query_imagem.value(0).toInt());
            imagem.setDescImagem(query_imagem.value(1).toString().toStdString());
            imagem.setTamanhoImagem(query_imagem.value(2).toFloat());
            qImg.load("./avistamentos/" + imagem.getIdImagem(), "PNG");
            imagem.setImgFile(qImg);
            v_imagens.push_back(imagem);
        }
        v_avists.at(i)->setImagens(v_imagens);

        query_equips.clear();
        query_equips.prepare("SELECT equip.id_equip, equip.nome_equip "
                             "FROM astros.Equipamento as equip, (SELECT id_equip FROM astros.Equip_avist WHERE id_avistamento = :id ) as rel "
                             "WHERE equip.id_equip = rel.id_equip");
        query_equips.bindValue(":id", v_avists.at(i)->getIdAvistamento());
        query_equips.exec();
        v_equips.clear();
        while(query_equips.next()){
            Equipamento *equipamento = new Equipamento();
            equipamento->setIdEquip(query_equips.value(0).toInt());
            equipamento->setNomeEquip(query_equips.value(1).toString().toStdString());
            v_equips.push_back(equipamento);
        }
        v_avists.at(i)->setEquipamentos(v_equips);

        query_astros.clear();
        query_astros.prepare("SELECT astro.id_astro, astro.nome_astro "
                             "FROM astros.Astro as astro, (SELECT id_astro FROM astros.Avist_astro WHERE id_avistamento = :id ) as rel "
                             "WHERE astro.id_astro = rel.id_astro");
        query_astros.bindValue(":id", v_avists.at(i)->getIdAvistamento());
        query_astros.exec();
        v_astros.clear();
        while(query_astros.next()){
            Astro *astro = new Astro();
            astro->SetId(query_astros.value(0).toInt());
            astro->SetName(query_astros.value(1).toString().toStdString());
            v_astros.push_back(astro);
        }
        v_avists.at(i)->setAstros(v_astros);
    }
}

Avistamento* FindAvistamento(size_t idAvistamento, const vector<Avistamento*> &v_avists){
    for(size_t i = 0; i < v_avists.size(); i++){
        if(idAvistamento == v_avists.at(i)->getIdAvistamento()){
            Avistamento *avistamento = v_avists.at(i);
            return avistamento;
        }
    }
    return NULL;
}
