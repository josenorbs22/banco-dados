#ifndef LOCAL_H
#define LOCAL_H

#include <iostream>
#include <vector>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFrame>

//namespace Ui {
//class Local;
//}

//class Local : public QFrame
//{
    //Q_OBJECT
class Local{
private:
    //Ui::Local *ui;

    int m_id_local;
    std::string m_cidade;
    std::string m_estado;
    std::string m_pais;
    std::string m_latitude;
    std::string m_longitude;

public:
    //explicit Local(QWidget *parent = nullptr);
    Local(){}
    ~Local();
    int getIdLocal() const{return m_id_local;}
    void setIdLocal(int id_local) {m_id_local = id_local;}
    std::string getCidade() const{return m_cidade;}
    void setCidade(std::string cidade) {m_cidade = cidade;}
    std::string getEstado() const{return m_estado;}
    void setEstado(std::string estado) {m_estado = estado;}
    std::string getPais() const{return m_pais;}
    void setPais(std::string pais) {m_pais = pais;}
    std::string getLatitude() const{return m_latitude;}
    void setLatitude(std::string latitude) {m_latitude = latitude;}
    std::string getLongitude() const{return m_longitude;}
    void setLongitude(std::string longitude) {m_longitude = longitude;}

    bool SaveLocal();
    bool EditLocal();
    bool DeleteLocal();
};
Q_DECLARE_METATYPE(Local*)

void LoadLocais(std::vector<Local*> &v_locais);
Local* FindLocal(size_t idLocal, const std::vector<Local*> &v_locais);

#endif // LOCAL_H
