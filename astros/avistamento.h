#ifndef AVISTAMENTO_H
#define AVISTAMENTO_H

#include <vector>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "usuario.h"
#include "local.h"
//#include "publicacao.h"
#include "astro.hpp"
#include "equipamento.h"
#include "imagem.h"

class Avistamento {
private:
    int m_id_avistamento;
    Usuario* m_usuario;
    Local* m_local;
    //Publicacao* m_publi;
    vector<Imagem> m_v_imagens;
    vector<Equipamento*> m_v_equips;
    vector<Astro*> m_v_astros;
    QDateTime m_data_avist;
    int m_id_publi;

public:
    Avistamento():m_id_avistamento(0), m_id_publi(0) {}
    ~Avistamento();
    int getIdAvistamento() const{return m_id_avistamento;}
    void setIdAvistamento(int id_avistamento) {m_id_avistamento = id_avistamento;}
    Usuario* getUsuario() const{return m_usuario;}
    void setUsuario(Usuario* usuario) {m_usuario = usuario;}
    Local* getLocal() const{return m_local;}
    void setLocal(Local* local) {m_local = local;}
//    Publicacao* getPublicacao() const{return m_publi;}
//    void setPublicacao(Publicacao* publicacao) {m_publi = publicacao;}
    vector<Imagem> getImagens() const{return m_v_imagens;}
    void setImagens(vector<Imagem> v_imagens) {m_v_imagens = v_imagens;}
    vector<Equipamento*> getEquipamentos() const{return m_v_equips;}
    void setEquipamentos(vector<Equipamento*> v_equips) {m_v_equips = v_equips;}
    vector<Astro*> getAstros() const{return m_v_astros;}
    void setAstros(vector<Astro*> v_astros) {m_v_astros = v_astros;}
    QDateTime getDataAvist() const{return m_data_avist;}
    void setDataAvist(QDateTime data_avist) {m_data_avist = data_avist;}
    int getIdP() const{return m_id_publi;}
    void setIdP(int id_publi) {m_id_publi = id_publi;}

    bool saveAvistamento();
    bool editAvistamento(vector<Astro*> &v_astros, vector<Equipamento*> &v_equips);
    bool deleteAvistamento();

};

Q_DECLARE_METATYPE(Avistamento*)
void loadAvistamentos(vector<Avistamento*> &v_avists, Usuario *usuario, vector<Local*> &v_locais);
Avistamento* FindAvistamento(size_t idAvistamento, const vector<Avistamento*> &v_avists);

#endif // AVISTAMENTO_H
