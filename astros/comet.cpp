#include "comet.hpp"

bool Comet::SaveComet(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Astro (nome_astro,"
                      " dec_astro,"
                      " ra_astro,"
                      " distance_astro,"
                      " excen_cometa,"
                      " periodo_cometa,"
                      " perielio_cometa, "
                      " afelio_cometa,"
                      " Astro_TIPO)"
                      " VALUES (:nome, :dec, :ra, :distance, :excen, :periodo, :perielio, :afelio, 1)");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":excen", this->m_eccentricity);
        query.bindValue(":periodo", this->m_period);
        query.bindValue(":perielio", this->m_perihelion);
        query.bindValue(":afelio", this->m_aphelion);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
//    ofstream filewriter("comet.txt");
//    if(!filewriter.is_open()) return false;

//    for(size_t i=0; i < v_comet.size(); i++){
//        Comet comet = v_comet.at(i);
//        filewriter << comet.GetId() << endl
//            << comet.GetName() << endl
//            << comet.GetEccentricity() << endl
//            << comet.GetPeriod() << endl
//            << comet.GetPerihelion() << endl
//            << comet.GetAphelion() << endl;
//    }
//    filewriter.close();
//    return true;
}
bool Comet::EditComet(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Astro"
                      " SET nome_astro = :nome, dec_astro = :dec, ra_astro = :ra, distance_astro = :distance,"
                      " excen_cometa = :excen, periodo_cometa = :periodo, perielio_cometa = :perielio, afelio_cometa = :afelio"
                      " WHERE id_astro = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":excen", this->m_eccentricity);
        query.bindValue(":periodo", this->m_period);
        query.bindValue(":perielio", this->m_perihelion);
        query.bindValue(":afelio", this->m_aphelion);
        query.bindValue(":id", this->m_id);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

void LoadComets(vector<Comet*> &v_comet){
    v_comet.clear();
    QSqlQuery query("SELECT id_astro, nome_astro, dec_astro,"
                    " ra_astro, distance_astro, excen_cometa,"
                    " periodo_cometa, perielio_cometa, afelio_cometa"
                    " FROM astros.Astro WHERE Astro_TIPO = 1");
    string tmp{""};
    while(query.next()){
        Comet *comet = new Comet();
        vector<int> dec, ra;
        comet->SetId(query.value(0).toInt());
        comet->SetName(QString(query.value(1).toString()).toStdString());
        stringstream ssdec(QString(query.value(2).toString()).toStdString());
        while(ssdec >> tmp)
            dec.push_back(stoi(tmp));
        stringstream ssra(QString(query.value(3).toString()).toStdString());
        while(ssra >> tmp)
            ra.push_back(stoi(tmp));
        comet->SetDec(dec);
        comet->SetRA(ra);
        comet->SetDistance(query.value(4).toDouble());
        comet->SetEccentricity(query.value(5).toDouble());
        comet->SetPeriod(query.value(6).toInt());
        comet->SetPerihelion(query.value(7).toDouble());
        comet->SetAphelion(query.value(8).toDouble());

        v_comet.push_back(comet);
    }
//    ifstream filereader("comet.txt");
//    v_comet.clear();
//    string tmp;
//    while(getline(filereader, tmp)){
//        if(tmp == "0" || tmp == "") break;
//        Comet comet;
//        comet.SetId(stol(tmp));
//        getline(filereader, tmp);
//        comet.SetName(tmp);
//        getline(filereader, tmp);
//        comet.SetEccentricity(stod(tmp));
//        getline(filereader, tmp);
//        comet.SetPeriod(stol(tmp));
//        getline(filereader, tmp);
//        comet.SetPerihelion(stod(tmp));
//        getline(filereader, tmp);
//        comet.SetAphelion(stod(tmp));

//        v_comet.push_back(comet);
//    }
//    filereader.close();
}

bool Comet::DeleteComet(){
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Astro WHERE id_astro = :id");
        query.bindValue(":id", this->m_id);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " << error.databaseText();
        return false;
    }
//    for(int i = 0; i < v_comet.size(); i++){
//        if(id == v_comet.at(i).GetId()){
//            v_comet.erase(v_comet.begin()+i);
//            return true;
//        }
//    }
//    return false;
}

Comet* FindComet(size_t idComet, const vector<Comet*> &v_comets){
    for(size_t i = 0; i < v_comets.size(); i++){
        if(idComet == v_comets.at(i)->GetId()){
            Comet *star = v_comets.at(i);
            return star;
        }
    }
    return NULL;
}
