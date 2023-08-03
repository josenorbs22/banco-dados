#include "equipamento.h"

Equipamento::Equipamento()
{

}

bool Equipamento::saveEquipamento(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Equipamento"
                            " (nome_equip,"
                            " marca_equip,"
                            " espec_equip,"
                            " id_tipo_equip)"
                            " VALUES (:nome, :marca, :espec, :id_tipo)");
        query.bindValue(":nome", QString::fromStdString(this->m_nome_equip));
        query.bindValue(":marca", QString::fromStdString(this->m_marca_equip));
        query.bindValue(":espec", QString::fromStdString(this->m_espec_equip));
        query.bindValue(":id_tipo", this->m_tipo_equip->getIdTipoEquip());
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Equipamento::editEquipamento(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Equipamento"
                            " SET nome_equip = :nome,"
                            " marca_equip = :marca,"
                            " espec_equip = :espec,"
                            " id_tipo_equip = :id_tipo"
                            " WHERE id_equipamento = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_nome_equip));
        query.bindValue(":marca", QString::fromStdString(this->m_marca_equip));
        query.bindValue(":espec", QString::fromStdString(this->m_espec_equip));
        query.bindValue(":id_tipo", this->m_tipo_equip->getIdTipoEquip());
        query.bindValue(":id", this->m_id_equip);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool Equipamento::deleteEquipamento(){
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Equipamento WHERE id_equip = :id");
        query.bindValue(":id", this->m_id_equip);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
}

void loadEquipamentos(std::vector<Equipamento*> &v_equips, std::vector<TipoEquipamento*> &v_tipo_equip){
    v_equips.clear();
    QSqlQuery query("SELECT id_equip, nome_equip, marca_equip, espec_equip, id_tipo_equip FROM astros.Equipamento");

    while(query.next()){
        Equipamento *equipamento = new Equipamento();
        equipamento->setIdEquip(query.value(0).toInt());
        equipamento->setNomeEquip(QString(query.value(1).toString()).toStdString());
        equipamento->setMarcaEquip(QString(query.value(2).toString()).toStdString());
        equipamento->setEspecEquip(QString(query.value(3).toString()).toStdString());
        TipoEquipamento *tipo_equip = FindTipoEquipamento(query.value(4).toInt(), v_tipo_equip);
        equipamento->setTipoEquip(tipo_equip);

        v_equips.push_back(equipamento);
    }
}

Equipamento* FindEquipamento(size_t idEquip, const std::vector<Equipamento*> &v_equips){
    for(size_t i = 0; i < v_equips.size(); i++){
        if(idEquip == v_equips.at(i)->getIdEquip()){
            Equipamento *equip = v_equips.at(i);
            return equip;
        }
    }
    return NULL;
}
