#include "planet.hpp"

Planet* FindPlanet(size_t idPlaneta, const vector<Planet*> &v_planets){
    for(size_t i = 0; i < v_planets.size(); i++){
        if(idPlaneta == v_planets.at(i)->GetId()){
            Planet *planet = v_planets.at(i);
            return planet;
        }
    }
    return NULL;

}

bool Planet::SavePlanet(){
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Astro (nome_astro,"
                      " dec_astro,"
                      " ra_astro,"
                      " distance_astro,"
                      " tamanho_planeta,"
                      " exoplaneta,"
                      " pos_planeta,"
                      " materiais_planeta,"
                      " Astro_TIPO)"
                      " VALUES (:nome, :dec, :ra, :distance, :tamanho, :exoplaneta, :pos, :materiais, 2)");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":tamanho", this->m_size);
        query.bindValue(":exoplaneta", this->m_exoplanet);
        query.bindValue(":pos", this->m_pos);
        query.bindValue(":materiais", QString::fromStdString(this->m_materials));
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
//    ofstream filewriter("planet.txt");
//    if(!filewriter.is_open()) return false;

//    for(size_t i=0; i < v_planet.size(); i++){
//        Planet planet = v_planet.at(i);
//        string exo = (planet.GetExoplanet() ? "Sim": "Nao");
//        filewriter << planet.GetId() << endl
//            << planet.GetName() << endl
//            << planet.GetDec().at(0) << endl
//            << planet.GetDec().at(1) << endl
//            << planet.GetDec().at(2) << endl
//            << planet.GetRA().at(0) << endl
//            << planet.GetRA().at(1) << endl
//            << planet.GetRA().at(2) << endl
//            << planet.GetDistance() << endl
//            << planet.GetSize() << endl
//            << exo << endl
//            << planet.GetSSName() << endl
//            << planet.GetPos() << endl
//            << planet.GetMaterials() << endl;
//    }
//    filewriter.close();
//    return true;
}

bool Planet::EditPlanet(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Astro"
                      " SET nome_astro = :nome, dec_astro = :dec, ra_astro = :ra, distance_astro = :distance,"
                      " tamanho_planeta = :tamanho, exoplaneta = :exoplaneta, pos_planeta = :pos, materiais_planeta = :materiais"
                      " WHERE id_astro = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":tamanho", this->m_size);
        query.bindValue(":exoplaneta", this->m_exoplanet);
        query.bindValue(":pos", this->m_pos);
        query.bindValue(":materiais", QString::fromStdString(this->m_materials));
        query.bindValue(":id", this->m_id);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

void LoadPlanets(vector<Planet*> &v_planet){
    v_planet.clear();
    QSqlQuery query("SELECT id_astro, nome_astro, dec_astro,"
                    " ra_astro, distance_astro, tamanho_planeta,"
                    " exoplaneta, pos_planeta, materiais_planeta, id_sissolar"
                    " FROM astros.Astro WHERE Astro_TIPO = 2");
    string tmp{""};
    while(query.next()){
        Planet *planet = new Planet();
        vector<int> dec, ra;
        planet->SetId(query.value(0).toInt());
        planet->SetName(QString(query.value(1).toString()).toStdString());
        stringstream ssdec(QString(query.value(2).toString()).toStdString());
        while(ssdec >> tmp)
            dec.push_back(stoi(tmp));
        stringstream ssra(QString(query.value(3).toString()).toStdString());
        while(ssra >> tmp)
            ra.push_back(stoi(tmp));
        planet->SetDec(dec);
        planet->SetRA(ra);
        planet->SetDistance(query.value(4).toDouble());
        planet->SetSize(query.value(5).toDouble());
        planet->SetExoplanet(query.value(6).toBool());
        planet->SetPos(query.value(7).toInt());
        planet->SetMaterials(QString(query.value(8).toString()).toStdString());
        planet->SetIdSSolar(query.value(9).toInt());

        v_planet.push_back(planet);
    }
//    ifstream filereader("planet.txt");
//    v_planet.clear();
//    string tmp;
//    while(getline(filereader, tmp)){
//        if(tmp == "0" || tmp == "") break;
//        Planet planet;
//        vector<int> dec, ra;
//        planet.SetId(stol(tmp));
//        getline(filereader, tmp);
//        planet.SetName(tmp);
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        planet.SetDec(dec);
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        planet.SetRA(ra);
//        getline(filereader, tmp);
//        planet.SetDistance(stof(tmp));
//        getline(filereader, tmp);
//        planet.SetSize(stof(tmp));
//        getline(filereader, tmp);
        
//        if(tmp == "Sim"){
//            planet.SetExoplanet(true);
//        } else
//            planet.SetExoplanet(false);

//        getline(filereader, tmp);
//        planet.SetSSName(tmp);
//        getline(filereader, tmp);
//        planet.SetPos(stoi(tmp));
//        getline(filereader, tmp);
//        planet.SetMaterials(tmp);

//        v_planet.push_back(planet);
//    }
//    filereader.close();
}

bool Planet::DeletePlanet(){
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Astro WHERE id_astro = :id");
        query.bindValue(":id", this->m_id);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " << error.databaseText();
        return false;
    }
//    for(int i = 0; i < v_planet.size(); i++){
//        if(id == v_planet.at(i).GetId()){
//            v_planet.erase(v_planet.begin()+i);
//            return true;
//        }
//    }
//    return false;
}
