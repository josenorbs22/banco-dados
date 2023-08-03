#include "star.hpp"

Star* FindStar(size_t idSol, const vector<Star*> &v_stars){
    for(size_t i = 0; i < v_stars.size(); i++){
        if(idSol == v_stars.at(i)->GetId()){
            Star *star = v_stars.at(i);
            return star;
        }
    }
    return NULL;
}

bool Star::SaveStar(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Astro (nome_astro,"
                      " dec_astro,"
                      " ra_astro,"
                      " distance_astro,"
                      " tipo_estrela,"
                      " massa_estrela,"
                      " raio_estrela,"
                      " mag_apa_estrela,"
                      " mag_abs_estrela,"
                      " Astro_TIPO)"
                      " VALUES (:nome, :dec, :ra, :distance, :tipo, :massa, :raio, :mag_apa, :mag_abs, 3)");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":tipo", QString::fromStdString(this->m_starType));
        query.bindValue(":massa", this->m_mass);
        query.bindValue(":raio", this->m_radius);
        query.bindValue(":mag_apa", this->m_appaMag);
        query.bindValue(":mag_abs", this->m_absMag);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
//    ofstream filewriter("star.txt");
//    if(!filewriter.is_open()) return false;

//    for(size_t i=0; i < v_star.size(); i++){
//        Star star = v_star.at(i);
//        filewriter << star.GetId() << endl
//            << star.GetName() << endl
//            << star.GetDec().at(0) << endl
//            << star.GetDec().at(1) << endl
//            << star.GetDec().at(2) << endl
//            << star.GetRA().at(0) << endl
//            << star.GetRA().at(1) << endl
//            << star.GetRA().at(2) << endl
//            << star.GetDistance() << endl
//            << star.GetStarType() << endl
//            << star.GetMass() << endl
//            << star.GetRadius() << endl
//            << star.GetAppaMag() << endl
//            << star.GetAbsMag() << endl;
//    }
//    filewriter.close();
//    return true;
}

bool Star::EditStar(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Astro"
                      " SET nome_astro = :nome, dec_astro = :dec, ra_astro = :ra, distance_astro = :distance,"
                      " tipo_estrela = :tipo, massa_estrela = :massa, raio_estrela = :raio, mag_apa_estrela = :mag_apa, mag_abs_estrela = :mag_abs"
                      " WHERE id_astro = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":tipo", QString::fromStdString(this->m_starType));
        query.bindValue(":massa", this->m_mass);
        query.bindValue(":raio", this->m_radius);
        query.bindValue(":mag_apa", this->m_appaMag);
        query.bindValue(":mag_abs", this->m_absMag);
        query.bindValue(":id", this->m_id);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error;
        return false;
    }
}

void LoadStars(vector<Star*> &v_star){
    v_star.clear();
    QSqlQuery query("SELECT id_astro, nome_astro, dec_astro, ra_astro,"
                    " distance_astro, tipo_estrela, massa_estrela,"
                    " raio_estrela, mag_apa_estrela, mag_abs_estrela, id_sissolar"
                    " FROM astros.Astro WHERE Astro_TIPO = 3");
    string tmp{""};
    while(query.next()){
        Star *star = new Star();
        vector<int> dec, ra;
        star->SetId(query.value(0).toInt());
        star->SetName(QString(query.value(1).toString()).toStdString());
        stringstream ssdec(QString(query.value(2).toString()).toStdString());
        while(ssdec >> tmp)
            dec.push_back(stoi(tmp));
        stringstream ssra(QString(query.value(3).toString()).toStdString());
        while(ssra >> tmp)
            ra.push_back(stoi(tmp));
        star->SetDec(dec);
        star->SetRA(ra);
        star->SetDistance(query.value(4).toDouble());
        star->SetStarType(QString(query.value(5).toString()).toStdString());
        star->SetMass(query.value(6).toDouble());
        star->SetRadius(query.value(7).toInt());
        star->SetAppaMag(query.value(8).toDouble());
        star->SetAbsMag(query.value(9).toDouble());
        star->SetIdSSolar(query.value(10).toInt());

        v_star.push_back(star);
    }
//    ifstream filereader("star.txt");
//    v_star.clear();
//    string tmp;
//    while(getline(filereader, tmp)){
//        if(tmp == "0" || tmp == "") break;
//        Star star;
//        vector<int> dec, ra;
//        star.SetId(stol(tmp));
//        getline(filereader, tmp);
//        star.SetName(tmp);
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        star.SetDec(dec);
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        star.SetRA(ra);
//        getline(filereader, tmp);
//        star.SetDistance(stod(tmp));
//        getline(filereader, tmp);
//        star.SetStarType(tmp);
//        getline(filereader, tmp);
//        star.SetMass(stod(tmp));
//        getline(filereader, tmp);
//        star.SetRadius(stol(tmp));
//        getline(filereader, tmp);
//        star.SetAppaMag(stod(tmp));
//        getline(filereader, tmp);
//        star.SetAbsMag(stod(tmp));

//        v_star.push_back(star);
//    }
//    filereader.close();
}

bool Star::DeleteStar(){
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Astro WHERE id_astro = :id");
        query.bindValue(":id", this->m_id);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " << error.databaseText();
        return false;
    }
//    for(int i = 0; i < v_star.size(); i++){
//        if(id == v_star.at(i).GetId()){
//            v_star.erase(v_star.begin()+i);
//            return true;
//        }
//    }
//    return false;
}
