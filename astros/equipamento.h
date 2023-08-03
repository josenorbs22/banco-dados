#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include <iostream>
#include <vector>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "tipoequipamento.h"


class Equipamento {

private:
    int m_id_equip;
    std::string m_nome_equip;
    std::string m_marca_equip;
    std::string m_espec_equip;
    TipoEquipamento* m_tipo_equip;

public:
    Equipamento();
    ~Equipamento() {}
    int getIdEquip() const{return m_id_equip;}
    void setIdEquip(int id_equip) {m_id_equip = id_equip;}
    std::string getNomeEquip() const{return m_nome_equip;}
    void setNomeEquip(std::string nome_equip) {m_nome_equip = nome_equip;}
    std::string getMarcaEquip()const{return m_marca_equip;}
    void setMarcaEquip(std::string marca_equip) {m_marca_equip = marca_equip;}
    std::string getEspecEquip()const{return m_espec_equip;}
    void setEspecEquip(std::string espec_equip) {m_espec_equip = espec_equip;}
    TipoEquipamento* getTipoEquip() const{return m_tipo_equip;}
    void setTipoEquip(TipoEquipamento *tipo_equip) {m_tipo_equip = tipo_equip;}

    bool saveEquipamento();
    bool editEquipamento();
    bool deleteEquipamento();
};

Q_DECLARE_METATYPE(Equipamento*)

void loadEquipamentos(std::vector<Equipamento*> &v_equips, std::vector<TipoEquipamento*> &v_tipo_equip);
Equipamento* FindEquipamento(size_t idEquip, const std::vector<Equipamento*> &v_equips);

#endif // EQUIPAMENTO_H
