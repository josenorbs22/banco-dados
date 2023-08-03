#include "tipoequipamento.h"


void loadTiposEquipamento(std::vector<TipoEquipamento*> &v_tipos_equip){
    v_tipos_equip.clear();
    QSqlQuery query("SELECT id_tipo_equip, desc_tipo_equip FROM astros.Tipo_equipamento");

    while(query.next()){
        TipoEquipamento *tipo_equip = new TipoEquipamento();
        tipo_equip->setIdTipoEquip(query.value(0).toInt());
        tipo_equip->setDescTipoEquip(query.value(1).toString().toStdString());

        v_tipos_equip.push_back(tipo_equip);
    }
}

TipoEquipamento* FindTipoEquipamento(size_t idTipoEquip, const std::vector<TipoEquipamento*> &v_tipo_equip){
    for(size_t i = 0; i < v_tipo_equip.size(); i++){
        if(idTipoEquip == v_tipo_equip.at(i)->getIdTipoEquip()){
            TipoEquipamento *tipo_equip = v_tipo_equip.at(i);
            return tipo_equip;
        }
    }
    return NULL;
}
