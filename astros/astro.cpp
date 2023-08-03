#include "astro.hpp"

bool Astro::SaveAstro(){
//    ofstream filewriter("astro.txt");
//    if(!filewriter.is_open()) return false;
    QSqlQuery query;
    try{
        query.prepare("INSERT INTO astros.Astro (nome_astro,"
                          " dec_astro,"
                          " ra_astro,"
                          " distance_astro,"
                          " Astro_TIPO)"
                          " VALUES (:nome, :dec, :ra, :distance, 4)");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
//    for(size_t i=0; i < v_astro.size(); i++){
//        Astro astro = v_astro.at(i);

//        filewriter << astro.GetId() << endl
//            << astro.GetName() << endl
//            << astro.GetDec().at(0) << endl
//            << astro.GetDec().at(1) << endl
//            << astro.GetDec().at(2) << endl
//            << astro.GetRA().at(0) << endl
//            << astro.GetRA().at(1) << endl
//            << astro.GetRA().at(2) << endl
//            << astro.GetDistance() << endl;

//    filewriter.close();
}

bool Astro::EditAstro(){
    QSqlQuery query;
    try{
        query.prepare("UPDATE astros.Astro"
                      " SET nome_astro = :nome, dec_astro = :dec, ra_astro = :ra, distance_astro = :distance"
                      " WHERE id_astro = :id");
        query.bindValue(":nome", QString::fromStdString(this->m_name));
        query.bindValue(":dec", QString::fromStdString(to_string(this->m_dec.at(0)) + " " + to_string(this->m_dec.at(1)) + " " + to_string(this->m_dec.at(2))));
        query.bindValue(":ra", QString::fromStdString(to_string(this->m_rA.at(0)) + " " + to_string(this->m_rA.at(1)) + " " + to_string(this->m_rA.at(2))));
        query.bindValue(":distance", this->m_distance);
        query.bindValue(":id", this->m_id);
        query.exec();
        return true;
    } catch(QSqlError error){
        qDebug() << "Erro na query: " << error.databaseText();
        return false;
    }
}

void LoadAstros(vector<Astro*> &v_astro){
    v_astro.clear();
    QSqlQuery query("SELECT id_astro, nome_astro, dec_astro, ra_astro, distance_astro, Astro_TIPO FROM astros.Astro");
    string tmp{""};

    while(query.next()){
        Astro *astro = new Astro();
        vector<int> dec, ra;
        astro->SetId(query.value(0).toInt());
        astro->SetName(QString(query.value(1).toString()).toStdString());
        stringstream ssdec(QString(query.value(2).toString()).toStdString());
        while(ssdec >> tmp)
            dec.push_back(stoi(tmp));
        stringstream ssra(QString(query.value(3).toString()).toStdString());
        while(ssra >> tmp)
            ra.push_back(stoi(tmp));
        astro->SetDec(dec);
        astro->SetRA(ra);
        astro->SetDistance(query.value(4).toDouble());
        astro->SetTipoAstro(query.value(5).toInt());

        v_astro.push_back(astro);
    }
//    ifstream filereader("astro.txt");

//    string tmp;
//    while(getline(filereader, tmp)){
//        if(tmp == "0" || tmp == "") break;
//        Astro astro;
//        vector<int> dec, ra;
//        astro.SetId(stol(tmp));
//        getline(filereader, tmp);
//        astro.SetName(tmp);
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        dec.push_back(stoi(tmp));
//        astro.SetDec(dec);
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        getline(filereader, tmp);
//        ra.push_back(stoi(tmp));
//        astro.SetRA(ra);
//        getline(filereader, tmp);
//        astro.SetDistance(stod(tmp));

//        v_astro.push_back(astro);
//    }
//    filereader.close();
}

bool Astro::DeleteAstro(){
//    bool done = false;
    QSqlQuery query;
    try {
        query.prepare("DELETE FROM astros.Astro WHERE id_astro = :id");
        query.bindValue(":id", this->m_id);
        return query.exec();
    } catch (QSqlError error) {
        qDebug() << "Erro do BD: " + error.databaseText();
        return false;
    }
//    for(int i = 0; i < v_astro.size(); i++){
//        if(id == v_astro.at(i).GetId()){
//            v_astro.erase(v_astro.begin()+i);
//            done = true;
//        }
//    }
//    return done;
}

size_t FindLastId(const vector<Astro*> &v_astro){
    size_t id = 0;
    for (size_t i = 0; i < v_astro.size(); i++){
        if(id < v_astro.at(i)->GetId()){
            id = v_astro.at(i)->GetId();
        }
    }
    return id;
}

Astro* FindAstro(size_t idAstro, const vector<Astro*> &v_astros){
    for(size_t i = 0; i < v_astros.size(); i++){
        if(idAstro == v_astros.at(i)->GetId()){
            Astro *star = v_astros.at(i);
            return star;
        }
    }
    return NULL;
}
