#ifndef PUBLICACAO_H
#define PUBLICACAO_H

#include <QStackedWidget>
#include <vector>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "avistamento.h"

//namespace Ui {
//class Publicacao;
//}

//class Publicacao : public QStackedWidget
//{
class Publicacao{
    //Q_OBJECT

private:
    //Ui::Publicacao *ui;
    int m_id_publi;
    std::string m_desc_publi;
    QDateTime m_data_publi;
    bool m_is_public;
    std::vector<Avistamento*> m_v_avists;

public:
    //explicit Publicacao(QWidget *parent = nullptr);
    Publicacao(){}
    ~Publicacao();
    int getIdPubli() const{return m_id_publi;}
    void setIdPubli(int id_publi){m_id_publi = id_publi;}
    std::string getDescPubli() const {return m_desc_publi;}
    void setDescPubli(std::string desc_publi) {m_desc_publi = desc_publi;}
    QDateTime getDataPubli() {return m_data_publi;}
    void setDataPubli(QDateTime data_publi) {m_data_publi = data_publi;}
    bool getIsPublic() const {return m_is_public;}
    void setIsPublic(bool is_public) {m_is_public = is_public;}
    std::vector<Avistamento*> getAvistamentos() const {return m_v_avists;}
    void setAvistamentos(std::vector<Avistamento*> v_avists) {m_v_avists = v_avists;}

    bool SavePublicacao();
    bool EditPublicacao();
    bool DeletePublicacao();
};

void LoadPublicacoes(std::vector<Publicacao> &v_publis, std::vector<Local*> &v_locais);

#endif // PUBLICACAO_H
