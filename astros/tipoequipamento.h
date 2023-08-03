#ifndef TIPOEQUIPAMENTO_H
#define TIPOEQUIPAMENTO_H

#include <iostream>
#include <vector>
#include <QSqlError>
#include <QSqlQuery>

class TipoEquipamento
{
public:
    TipoEquipamento(){}
    ~TipoEquipamento(){}
    int getIdTipoEquip() const{return m_id_tipo_equip;}
    void setIdTipoEquip(int id_tipo_equip) {m_id_tipo_equip = id_tipo_equip;}
    std::string getDescTipoEquip() const{return m_desc_tipo_equip;}
    void setDescTipoEquip(std::string desc_tipo_equip) {m_desc_tipo_equip = desc_tipo_equip;}

private:
    int m_id_tipo_equip;
    std::string m_desc_tipo_equip;
};
Q_DECLARE_METATYPE(TipoEquipamento*)

void loadTiposEquipamento(std::vector<TipoEquipamento*> &v_tipos_equip);
TipoEquipamento* FindTipoEquipamento(size_t idTipoEquip, const std::vector<TipoEquipamento*> &v_tipo_equip);

#endif // TIPOEQUIPAMENTO_H
