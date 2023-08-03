#include "planet.hpp"
#include "star.hpp"
#include "solar-system.hpp"

bool SolarSystem::SaveSolarSystem(){
//    ofstream filewriter("solar-system.txt");
//    if(!filewriter.is_open()) return false;

//    for(size_t i=0; i < v_ssystem.size(); i++){
//        SolarSystem ssystem = v_ssystem.at(i);
    
//        filewriter << ssystem.GetId() << endl << ssystem.GetName() << endl;

//        for (size_t i = 0; i < ssystem.GetStars().size(); i++){
//            filewriter << ssystem.GetStars().at(i)->GetId() << endl;
//        }
//        filewriter << "--" << endl;
//        for (size_t i = 0; i < ssystem.GetPlanets().size(); i++){
//            filewriter << ssystem.GetPlanets().at(i)->GetId() << endl;
//        }
//        filewriter << "--" << endl;
        
//    }
//    filewriter.close();
//    return true;
    QSqlQuery query, query_astros;
    try{
        query.prepare("INSERT INTO astros.Sistema_solar (nome_sissolar)"
                      " VALUES (:nome)");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.exec();
        QVariantList ids_astros;
        QVariantList ids_ssystems;
        for(size_t i = 0; i < this->m_planet.size(); i++){
            ids_astros << this->m_planet.at(i)->GetId();
            ids_ssystems << query.lastInsertId();
        }
        for(size_t i = 0; i < this->m_star.size(); i++){
            ids_astros << this->m_star.at(i)->GetId();
            ids_ssystems << query.lastInsertId();
        }
        query_astros.clear();
        query_astros.prepare("UPDATE astros.Astro SET id_sissolar = :id WHERE id_astro = :id_astro");
        query_astros.bindValue(":id", ids_ssystems);
        query_astros.bindValue(":id_astro", ids_astros);
        query_astros.execBatch();

        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

bool SolarSystem::EditSolarSystem(){
    QSqlQuery query, query_astros;
    try{
        query.prepare("UPDATE astros.Sistema_solar SET nome_sissolar = :nome"
                      " WHERE id_sissolar = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":id", this->m_id);
        query.exec();
        query_astros.prepare("UPDATE astros.Astro SET id_sissolar = NULL WHERE id_sissolar = :id");
        query_astros.bindValue(":id", this->m_id);
        QVariantList ids_astros;
        for(size_t i = 0; i < this->m_planet.size(); i++){
            ids_astros << this->m_planet.at(i)->GetId();
        }
        for(size_t i = 0; i < this->m_star.size(); i++){
            ids_astros << this->m_star.at(i)->GetId();
        }
        query_astros.clear();
        query_astros.prepare("UPDATE astros.Astro SET id_sissolar = :id WHERE id_astro = :id_astro");
        query_astros.bindValue(":id", this->m_id);
        query_astros.bindValue(":id_astro", ids_astros);
        query_astros.execBatch();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

void LoadSolarSystems(vector<SolarSystem> &v_ssystem, const vector<Star*> &v_star, const vector<Planet*> &v_planet){
    v_ssystem.clear();
    vector<Star*> m_v_star;
    vector<Planet*> m_v_planet;
    QSqlQuery query, query_planeta, query_estrela;
    query.prepare("SELECT id_sissolar, nome_sissolar FROM astros.Sistema_solar");
    query.exec();



    while(query.next()){
        SolarSystem sissolar;
        sissolar.SetId(query.value(0).toInt());
        sissolar.SetName(query.value(1).toString().toStdString());

        v_ssystem.push_back(sissolar);
    }

    for(size_t i = 0; i < v_ssystem.size(); i++){
        query_planeta.clear();
        query_planeta.prepare("SELECT id_astro FROM astros.Astro WHERE Astro_TIPO = 2 AND id_sissolar = :id");
        query_planeta.bindValue(":id", v_ssystem.at(i).GetId());
        query_planeta.exec();
        m_v_planet.clear();
        while(query_planeta.next()){
            m_v_planet.push_back(FindPlanet(query_planeta.value(0).toInt(), v_planet));
        }
        v_ssystem.at(i).SetPlanets(m_v_planet);

        query_estrela.clear();
        query_estrela.prepare("SELECT id_astro FROM astros.Astro WHERE Astro_TIPO = 3 AND id_sissolar = :id");
        query_estrela.bindValue(":id", v_ssystem.at(i).GetId());
        query_estrela.exec();
        m_v_star.clear();
        while(query_estrela.next()){
            m_v_star.push_back(FindStar(query_estrela.value(0).toInt(), v_star));
        }
        v_ssystem.at(i).SetStars(m_v_star);
    }
//    ifstream filereader("solar-system.txt");
//    v_ssystem.clear();
//    string tmp;
//    while(getline(filereader, tmp)){
//        if(tmp == "0" || tmp == "") break;
//        vector<size_t> idsSol, idsPlanets;
//        SolarSystem ssystem;
//        vector<Star*> stars;
//        vector<Planet*> planets;

//        ssystem.SetId(stol(tmp));
//        getline(filereader, tmp);
//        ssystem.SetName(tmp);
//        while(getline(filereader, tmp)){
//            if(tmp != "--"){
//                idsSol.push_back(stol(tmp));
//                continue;
//            } else
//                break;
//        }
//        for(size_t i = 0; i < idsSol.size(); i++){
//            Star *star = FindStar(idsSol.at(i), v_star);
//            if(star != NULL)
//                stars.push_back(star);
//        }
//        ssystem.SetStars(stars);

//        while(getline(filereader, tmp)){
//            if(tmp != "--"){
//                idsPlanets.push_back(stol(tmp));
//                continue;
//            } else
//                break;
//        }
//        for(size_t i = 0; i < idsPlanets.size(); i++){
//            Planet *planet = FindPlanet(idsPlanets.at(i), v_planet);
//            if(planet != NULL)
//                planets.push_back(planet);
//        }
//        ssystem.SetPlanets(planets);

//        v_ssystem.push_back(ssystem);
//    }
//    filereader.close();
}

bool SolarSystem::DeleteSolarSystem(){
    QSqlQuery query, query_astros;
    try {
        query_astros.prepare("UPDATE astros.Astro SET id_sissolar = NULL WHERE id_sissolar = :id");
        query_astros.bindValue(":id", this->m_id);
        query_astros.exec();
        query.prepare("DELETE FROM astros.Sistema_solar WHERE id_sissolar = :id");
        query.bindValue(":id", this->m_id);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
//    for(int i = 0; i < v_ssystem.size(); i++){
//        if(id == v_ssystem.at(i).GetId()){
//            v_ssystem.erase(v_ssystem.begin()+i);
//            return true;
//        }
//    }
//    return false;
}

size_t FindLastId(const vector<SolarSystem> &v_ssystem){
    size_t id = 0;
    for (size_t i = 0; i < v_ssystem.size(); i++){
        if(id < v_ssystem.at(i).GetId()){
            id =v_ssystem.at(i).GetId();
        }
    }
    return id;
}
