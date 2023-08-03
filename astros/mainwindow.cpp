#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(Usuario* usuario, QWidget *parent)
    : m_usuario(usuario), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadStars(v_stars);
    LoadPlanets(v_planets);
    LoadComets(v_comets);
    LoadAstros(v_astros);
    LoadSolarSystems(v_ssystems, v_stars, v_planets);
    LoadLocais(v_locais);
    loadAvistamentos(v_avists, m_usuario, v_locais);
    LoadPublicacoes(v_publis, v_locais);
    loadTiposEquipamento(v_tipo_equip);
    loadEquipamentos(v_equips, v_tipo_equip);
    v_comboPlanet.push_back(ui->planeta1);
    v_comboStar.push_back(ui->estrela1);
    v_comboAstro.push_back(ui->astro1);
    v_comboEquip.push_back(ui->equip1);
    v_comboAvist.push_back(ui->avist1);
    for(size_t i = 0; i < v_avists.size(); i++){
        if(v_avists.at(i)->getIdP() == 0)
            ui->avist1->addItem(v_avists.at(i)->getDataAvist().toString("dd/MM/yyyy") + QString::fromStdString(v_avists.at(i)->getLocal()->getCidade() + ", " + v_avists.at(i)->getLocal()->getEstado()), QVariant::fromValue(v_avists.at(i)));
    }
    FillFeed();
    ui->stackedWidget->setCurrentIndex(7);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_novoAstro_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
    isEditing = false;
    ui->nomeAstro->clear();
    ui->horaDec->clear();
    ui->minDec->clear();
    ui->secDec->clear();
    ui->grauAR->clear();
    ui->minAR->clear();
    ui->secAR->clear();
    ui->distanciaAstro->clear();
    ui->tipoEstrela->clear();
    ui->massaEstelar->clear();
    ui->raioEstelar->clear();
    ui->magApa->clear();
    ui->magAbs->clear();
    ui->tamanhoPlaneta->clear();
    ui->exoPlaneta->setChecked(false);
    ui->nomeSSPLaneta->clear();
    ui->posSSPlaneta->clear();
    ui->materiaisPlaneta->clear();
    ui->excenCometa->clear();
    ui->periodoCometa->clear();
    ui->perielioCometa->clear();
    ui->afelioCometa->clear();
    ui->saveAstro->setText("Salvar");
    ui->tipoAstro->setDisabled(false);
}


void MainWindow::on_listaAstros_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableAstro->clearContents();
    ui->tableStars->clearContents();
    ui->tablePlanets->clearContents();
    ui->tableComets->clearContents();
    ui->tableAstro->setRowCount(0);
    ui->tableStars->setRowCount(0);
    ui->tablePlanets->setRowCount(0);
    ui->tableComets->setRowCount(0);

    for(size_t i = 0; i < v_astros.size(); i++){
        ui->tableAstro->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_astros.at(i)->GetId()))
             << QString::fromStdString(v_astros.at(i)->GetName())
             << (QString::fromStdString(to_string(v_astros.at(i)->GetDec().at(0))) + "h " + QString::fromStdString(to_string(v_astros.at(i)->GetDec().at(1))) + "m " + QString::fromStdString(to_string(v_astros.at(i)->GetDec().at(2))) + "s ")
             << (QString::fromStdString(to_string(v_astros.at(i)->GetRA().at(0))) + "° " + QString::fromStdString(to_string(v_astros.at(i)->GetRA().at(1))) + "m " + QString::fromStdString(to_string(v_astros.at(i)->GetRA().at(2))) + "s ")
             << QString::fromStdString(to_string(v_astros.at(i)->GetDistance()));
        for(size_t j = 0; j < 5; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tableAstro->setItem(i,j,item);
        }
    }

    for(size_t i = 0; i < v_stars.size(); i++){
        ui->tableStars->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_stars.at(i)->GetId()))
             << QString::fromStdString(v_stars.at(i)->GetStarType())
             << QString::fromStdString(to_string(v_stars.at(i)->GetMass()))
             << QString::fromStdString(to_string(v_stars.at(i)->GetRadius()))
             << QString::fromStdString(to_string(v_stars.at(i)->GetAppaMag()))
             << QString::fromStdString(to_string(v_stars.at(i)->GetAbsMag()));
        for(size_t j = 0; j < 6; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tableStars->setItem(i,j,item);
        }
    }

    for(size_t i = 0; i < v_planets.size(); i++){
        ui->tablePlanets->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_planets.at(i)->GetId()))
             << QString::fromStdString(to_string(v_planets.at(i)->GetSize()))
             << (v_planets.at(i)->GetExoplanet()? "Sim" : "Não")
             << QString::fromStdString(v_planets.at(i)->GetSSName())
             << QString::fromStdString(to_string(v_planets.at(i)->GetPos()))
             << QString::fromStdString(v_planets.at(i)->GetMaterials());
        for(size_t j = 0; j < 6; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tablePlanets->setItem(i,j,item);
        }
    }

    for(size_t i = 0; i < v_comets.size(); i++){
        ui->tableComets->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_comets.at(i)->GetId()))
             << QString::fromStdString(to_string(v_comets.at(i)->GetEccentricity()))
             << QString::fromStdString(to_string(v_comets.at(i)->GetPeriod()))
             << QString::fromStdString(to_string(v_comets.at(i)->GetPerihelion()))
             << QString::fromStdString(to_string(v_comets.at(i)->GetAphelion()));
        for(size_t j = 0; j < 5; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tableComets->setItem(i,j,item);
        }
    }

}


void MainWindow::on_novoSistemaSolar_clicked(){
    ui->stackedWidget->setCurrentIndex(4);
    for(size_t i = 0; i < v_planets.size(); i++){
        if(v_planets.at(i)->GetIdSSolar() == 0)
            ui->planeta1->addItem(QString::fromStdString(v_planets.at(i)->GetName()), QVariant::fromValue(v_planets.at(i)));
    }
    for(size_t i = 0; i < v_stars.size(); i++){
        if(v_stars.at(i)->GetIdSSolar() == 0)
            ui->estrela1->addItem(QString::fromStdString(v_stars.at(i)->GetName()), QVariant::fromValue(v_stars.at(i)));
    }
}


void MainWindow::on_listaSistemaSolares_clicked(){
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableSSystems->clearContents();
    ui->tableSSystems->setRowCount(0);
    for(size_t i = 0; i < v_ssystems.size(); i++){
        ui->tableSSystems->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_ssystems.at(i).GetId()));
        data << QString::fromStdString(v_ssystems.at(i).GetName());
        QString planetas;
        for(size_t j = 0; j < v_ssystems.at(i).GetPlanets().size(); j++){
            planetas += QString::fromStdString(v_ssystems.at(i).GetPlanets().at(j)->GetName()) + ", ";
        }
        data << planetas;
        QString estrelas;
        for(size_t j = 0; j < v_ssystems.at(i).GetStars().size(); j++){
            estrelas += QString::fromStdString(v_ssystems.at(i).GetStars().at(j)->GetName()) + ", ";
        }
        data << estrelas;
        for(size_t j = 0; j < 4; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tableSSystems->setItem(i,j,item);
        }
    }
}

void MainWindow::FillPlanetsComboBox(){
    QComboBox *comboBoxPlanet = new QComboBox(ui->formLayoutWidget_2);
    string nameComboBox = "planeta" + to_string(iPlanets);
    comboBoxPlanet->setObjectName(QString::fromStdString(nameComboBox));
    v_comboPlanet.push_back(comboBoxPlanet);
    ui->planetsSS->addWidget(comboBoxPlanet);
    for(size_t i = 0; i < v_planets.size(); i++){
        if(v_planets.at(i)->GetIdSSolar() == 0)
            comboBoxPlanet->addItem(QString::fromStdString(v_planets.at(i)->GetName()), QVariant::fromValue(v_planets.at(i)));
    }
}

void MainWindow::FillStarsComboBox(){
    QComboBox *comboBoxStar = new QComboBox(ui->formLayoutWidget_2);
    string nameComboBox = "estrela" + to_string(iStars);
    comboBoxStar->setObjectName(QString::fromStdString(nameComboBox));
    v_comboStar.push_back(comboBoxStar);
    ui->starsSS->addWidget(comboBoxStar);
    for(size_t i = 0; i < v_stars.size(); i++){
        if(v_stars.at(i)->GetIdSSolar() == 0)
            comboBoxStar->addItem(QString::fromStdString(v_stars.at(i)->GetName()), QVariant::fromValue(v_stars.at(i)));
    }
}

void MainWindow::FillAstrosComboBox(){
    QComboBox *comboBoxAstro = new QComboBox(ui->formLayoutWidget_8);
    string nameComboBox = "astro" + to_string(nAstros);
    comboBoxAstro->setObjectName(QString::fromStdString(nameComboBox));
    v_comboAstro.push_back(comboBoxAstro);
    ui->astrosAvist->addWidget(comboBoxAstro);
    for(size_t i = 0; i < v_astros.size(); i++){
        comboBoxAstro->addItem(QString::fromStdString(v_astros.at(i)->GetName()), QVariant::fromValue(v_astros.at(i)));
    }
}

void MainWindow::FillLocaisComboBox(){
    for(size_t i = 0; i < v_locais.size(); i++){
        ui->locaisAvist->addItem(QString::fromStdString(v_locais.at(i)->getCidade() + ", "
                                                           + v_locais.at(i)->getEstado() + ", "
                                                           + v_locais.at(i)->getPais() + " - "
                                                           + v_locais.at(i)->getLatitude() + "; "
                                                           + v_locais.at(i)->getLongitude()),
                                                            QVariant::fromValue(v_locais.at(i)));
    }
}

void MainWindow::FillEquipsComboBox(){
    QComboBox *comboBoxEquip = new QComboBox(ui->formLayoutWidget_7);
    string nameComboBox = "equip" + to_string(nEquips);
    comboBoxEquip->setObjectName(QString::fromStdString(nameComboBox));
    v_comboEquip.push_back(comboBoxEquip);
    ui->equipsAvist->addWidget(comboBoxEquip);
    for(size_t i = 0; i < v_equips.size(); i++){
        comboBoxEquip->addItem(QString::fromStdString(v_equips.at(i)->getNomeEquip()), QVariant::fromValue(v_equips.at(i)));
    }
}

void MainWindow::FillAvistsComboBox(){
    QComboBox *comboBoxAvist = new QComboBox(ui->formLayoutWidget_9);
    string nameComboBox = "avist" + to_string(nAvists);
    comboBoxAvist->setObjectName(QString::fromStdString(nameComboBox));
    v_comboAvist.push_back(comboBoxAvist);
    ui->avistPubli->addWidget(comboBoxAvist);
    for(size_t i = 0; i < v_avists.size(); i++){
        if(v_avists.at(i)->getIdP() == 0)
            comboBoxAvist->addItem(v_avists.at(i)->getDataAvist().toString("dd/MM/yyyy") + QString::fromStdString(v_avists.at(i)->getLocal()->getCidade() + ", " + v_avists.at(i)->getLocal()->getEstado()), QVariant::fromValue(v_avists.at(i)));
    }
}

void MainWindow::FillFeed(){
    size_t tamanho = v_widgetsPubli.size();
    v_widgetsPubli.clear();
    for(size_t i = 0; i < tamanho; i++){
        delete ui->layoutFeed->itemAt(0)->widget();
    }

    for(size_t i = 0; i < v_publis.size(); i++){
        Publicacao_ui *publi_ui = new Publicacao_ui(v_publis.at(i));
        ui->layoutFeed->addWidget(publi_ui);
        v_widgetsPubli.push_back(publi_ui);
    }
}

void MainWindow::on_tipoAstro_currentIndexChanged(int index){
    ui->stackedWidget_2->setCurrentIndex(index);
}


void MainWindow::on_tipoAstroLista_currentIndexChanged(int index){
    ui->stackedWidget_3->setCurrentIndex(index);
}


void MainWindow::on_morePlanet_2_clicked(){
    iPlanets++;
    FillPlanetsComboBox();
}


void MainWindow::on_moreStar_2_clicked(){
    iStars++;
    FillStarsComboBox();
}


void MainWindow::on_removePlanet_2_clicked(){
    iPlanets--;
    if(iPlanets > 0){
        v_comboPlanet.erase(v_comboPlanet.begin() + iPlanets - 1);
        delete ui->planetsSS->itemAt(iPlanets - 1)->widget();

    }
}


void MainWindow::on_removeStar_2_clicked(){
    iStars--;
    if(iStars > 0){
        v_comboStar.erase(v_comboStar.begin()+iStars - 1);
        delete ui->starsSS->itemAt(iStars - 1)->widget();
    }

}


void MainWindow::on_saveAstro_clicked(){
    bool done{false};
    Astro astro;
    vector<int> v_dec;
    v_dec.push_back(ui->horaDec->value());
    v_dec.push_back(ui->minDec->value());
    v_dec.push_back(ui->secDec->value());
    vector<int> v_ra;
    v_ra.push_back(ui->grauAR->value());
    v_ra.push_back(ui->minAR->value());
    v_ra.push_back(ui->secAR->value());


    astro.SetName(ui->nomeAstro->text().toStdString());
    astro.SetDec(v_dec);
    astro.SetRA(v_ra);
    astro.SetDistance( ui->distanciaAstro->value());
    astro.SetTipoAstro(4);
    if(ui->tipoAstro->currentIndex() == 1){
        Star star(astro);
        star.SetTipoAstro(3);
        star.SetStarType(ui->tipoEstrela->text().toStdString());
        star.SetMass(ui->massaEstelar->value());
        star.SetRadius(ui->raioEstelar->value());
        star.SetAppaMag(ui->magApa->value());
        star.SetAbsMag(ui->magAbs->value());
        if(isEditing){
            QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
            string s_id = itens.at(0)->text().toStdString();
            size_t id = stol(s_id);
            star.SetId(id);
            done = star.EditStar();
        } else
            done = star.SaveStar();

        ui->tipoEstrela->clear();
        ui->massaEstelar->clear();
        ui->raioEstelar->clear();
        ui->magApa->clear();
        ui->magAbs->clear();
    } else if(ui->tipoAstro->currentIndex() == 2){
        Planet planet(astro);
        planet.SetTipoAstro(2);
        planet.SetSize(ui->tamanhoPlaneta->value());
        planet.SetExoplanet(ui->exoPlaneta->isChecked());
        planet.SetSSName(ui->nomeSSPLaneta->text().toStdString());
        planet.SetPos(ui->posSSPlaneta->value());
        planet.SetMaterials(ui->materiaisPlaneta->text().toStdString());

        if(isEditing){
            QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
            string s_id = itens.at(0)->text().toStdString();
            size_t id = stol(s_id);
            planet.SetId(id);
            done = planet.EditPlanet();
        } else
            done = planet.SavePlanet();

        ui->tamanhoPlaneta->clear();
        ui->exoPlaneta->setChecked(false);
        ui->nomeSSPLaneta->clear();
        ui->posSSPlaneta->clear();
        ui->materiaisPlaneta->clear();
    } else if(ui->tipoAstro->currentIndex() == 3){
        Comet comet(astro);
        comet.SetTipoAstro(1);
        comet.SetEccentricity(ui->excenCometa->value());
        comet.SetPeriod(ui->periodoCometa->value());
        comet.SetPerihelion(ui->perielioCometa->value());
        comet.SetAphelion(ui->afelioCometa->value());

        if(isEditing){
            QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
            string s_id = itens.at(0)->text().toStdString();
            size_t id = stol(s_id);
            comet.SetId(id);
            done = comet.EditComet();
        } else
            done = comet.SaveComet();

        ui->excenCometa->clear();
        ui->periodoCometa->clear();
        ui->perielioCometa->clear();
        ui->afelioCometa->clear();
    } else {
        if(isEditing){
            QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
            string s_id = itens.at(0)->text().toStdString();
            size_t id = stol(s_id);
            astro.SetId(id);
            done = astro.EditAstro();
        } else {
            done = astro.SaveAstro();
        }
    }

    ui->nomeAstro->clear();
    ui->horaDec->clear();
    ui->minDec->clear();
    ui->secDec->clear();
    ui->grauAR->clear();
    ui->minAR->clear();
    ui->secAR->clear();
    ui->distanciaAstro->clear();

    LoadStars(v_stars);
    LoadPlanets(v_planets);
    LoadComets(v_comets);
    LoadAstros(v_astros);

    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(done)
        message.setText("Astro salvo com sucesso!");
    else
        message.setText("Algo deu errado");
    message.setFixedSize(300,100);
    message.exec();

    ui->saveAstro->setText("Salvar");
    isEditing = false;
}


void MainWindow::on_deleteAstro_clicked(){
    bool done{false};
    Astro astro;
    QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
    string s_id = itens.at(0)->text().toStdString();
    size_t id = stol(s_id);
    astro.SetId(id);
    done = astro.DeleteAstro();

    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(done)
        message.setText("Astro deletado!");
    else
        message.setText("Algo errado aconteceu!");
    message.setFixedSize(325,100);
    message.exec();

    LoadStars(v_stars);
    LoadPlanets(v_planets);
    LoadComets(v_comets);
    LoadAstros(v_astros);

    MainWindow::on_listaAstros_clicked();
}


void MainWindow::on_saveSSystem_clicked(){
    idSSystem++;
    SolarSystem ssystem;
    Planet *planet;
    Star *star;
    vector<Planet*> planets;
    vector<Star*> stars;
    ssystem.SetName(ui->nomeSSystem->text().toStdString());
    for(int i = 0; i < iPlanets; i++){
        planet = v_comboPlanet.at(i)->currentData().value<Planet*>();
        planets.push_back(planet);
    }
    ssystem.SetPlanets(planets);

    for(int i = 0; i < iStars; i++){
        star = v_comboStar.at(i)->currentData().value<Star*>();
        stars.push_back(star);
    }
    ssystem.SetStars(stars);

    ui->nomeSSystem->clear();

    for(int i = 1; i < iPlanets; i++){
        delete v_comboPlanet.at(i);
    }
    for(int i = 1; i < iStars; i++){
        delete v_comboStar.at(i);
    }
    v_comboStar.clear();
    v_comboPlanet.clear();
    iPlanets = 1;
    iStars = 1;
    LoadPlanets(v_planets);
    LoadStars(v_stars);
    for(size_t i = 0; i < v_planets.size(); i++){
        if(v_planets.at(i)->GetIdSSolar() == 0)
            ui->planeta1->addItem(QString::fromStdString(v_planets.at(i)->GetName()), QVariant::fromValue(v_planets.at(i)));
    }
    for(size_t i = 0; i < v_stars.size(); i++){
        if(v_stars.at(i)->GetIdSSolar() == 0)
            ui->estrela1->addItem(QString::fromStdString(v_stars.at(i)->GetName()), QVariant::fromValue(v_stars.at(i)));
    }
    v_comboStar.push_back(ui->estrela1);
    v_comboPlanet.push_back(ui->planeta1);

    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(ssystem.SaveSolarSystem())
        message.setText("Sistema Solar salvo com sucesso!");
    else
        message.setText("Algo deu errado ao salvar o Sistema Solar!");
    message.setFixedSize(325,100);
    message.exec();
    LoadSolarSystems(v_ssystems, v_stars, v_planets);
}


void MainWindow::on_pushButton_clicked(){
    SolarSystem solarsystem;
    QList<QTableWidgetItem*> itens = ui->tableSSystems->selectedItems();
    string s_id = itens.at(0)->text().toStdString();
    size_t id = stol(s_id);
    solarsystem.SetId(id);
    solarsystem.DeleteSolarSystem();


    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(solarsystem.DeleteSolarSystem())
        message.setText("Sistema Solar deletado!");
    else
        message.setText("Não deu para deletar o Sistema Solar");
    message.setFixedSize(325,100);
    message.exec();
    LoadSolarSystems(v_ssystems, v_stars, v_planets);
    MainWindow::on_listaSistemaSolares_clicked();
}


void MainWindow::on_editAstro_clicked(){
    QList<QTableWidgetItem*> itens = ui->tableAstro->selectedItems();
    if(itens.size() > 0){
        string s_id = itens.at(0)->text().toStdString();
        size_t id = stol(s_id);
        Astro *astro = FindAstro(id, v_astros);
        Star *star = FindStar(id, v_stars);
        Planet *planet = FindPlanet(id, v_planets);
        Comet *comet = FindComet(id, v_comets);
        if(astro != NULL){
            ui->stackedWidget->setCurrentIndex(0);
            isEditing = true;
            ui->saveAstro->setText("Editar");
            ui->nomeAstro->setText(QString::fromStdString(astro->GetName()));
            ui->horaDec->setValue(astro->GetDec().at(0));
            ui->minDec->setValue(astro->GetDec().at(1));
            ui->secDec->setValue(astro->GetDec().at(2));
            ui->grauAR->setValue(astro->GetRA().at(0));
            ui->minAR->setValue(astro->GetRA().at(1));
            ui->secAR->setValue(astro->GetRA().at(2));
            ui->distanciaAstro->setValue(astro->GetDistance());
        }

        if(star != NULL){
            ui->stackedWidget_2->setCurrentIndex(1);
            ui->tipoAstro->setCurrentIndex(1);
            ui->tipoEstrela->setText(QString::fromStdString(star->GetStarType()));
            ui->massaEstelar->setValue(star->GetMass());
            ui->raioEstelar->setValue(star->GetRadius());
            ui->magApa->setValue(star->GetAppaMag());
            ui->magAbs->setValue(star->GetAbsMag());
        } else if(planet != NULL){
            ui->stackedWidget_2->setCurrentIndex(2);
            ui->tipoAstro->setCurrentIndex(2);
            ui->tamanhoPlaneta->setValue(planet->GetSize());
            ui->exoPlaneta->setChecked(planet->GetExoplanet());
            ui->nomeSSPLaneta->setText(QString::fromStdString(planet->GetSSName()));
            ui->posSSPlaneta->setValue(planet->GetPos());
            ui->materiaisPlaneta->setText(QString::fromStdString(planet->GetMaterials()));
        } else if(comet != NULL){
            ui->stackedWidget_2->setCurrentIndex(3);
            ui->tipoAstro->setCurrentIndex(3);
            ui->excenCometa->setValue(comet->GetEccentricity());
            ui->periodoCometa->setValue(comet->GetPeriod());
            ui->perielioCometa->setValue(comet->GetPerihelion());
            ui->afelioCometa->setValue(comet->GetAphelion());
        }
        ui->tipoAstro->setDisabled(true);
    }
}


void MainWindow::on_actionFoto_triggered()
{
    QMessageBox perfil;
    perfil.setText("José Norberto Fagundes Isaias");
    perfil.setInformativeText("Matrícula: 19202785");
    perfil.setIconPixmap(QPixmap(":/perfil/fotoPerfil.png"));
    perfil.exec();
}


void MainWindow::on_selImagens_clicked()
{
    QFileDialog fd;
    listaImagens = fd.getOpenFileNames(this, "Selecione uma ou mais imagens", "./", "Images (*.png *.jpg)");
    ui->listadeImagens->addItems(listaImagens);
}


void MainWindow::on_novoLocal_clicked()
{
    Local_ui *loc_ui = new Local_ui(this->v_locais, this);
    loc_ui->show();
}


void MainWindow::on_maisAstros_clicked()
{
    nAstros++;
    FillAstrosComboBox();
}


void MainWindow::on_menosAstros_clicked()
{
    nAstros--;
    if(nAstros > 0){
        v_comboAstro.erase(v_comboAstro.begin()+nAstros - 1);
        delete ui->astrosAvist->itemAt(nAstros - 1)->widget();
    }
}


void MainWindow::on_maisEquip_clicked()
{
    nEquips++;
    FillEquipsComboBox();
}


void MainWindow::on_menosEquip_clicked()
{
    nEquips--;
    if(nEquips > 0){
        v_comboEquip.erase(v_comboEquip.begin()+nEquips - 1);
        delete ui->equipsAvist->itemAt(nEquips - 1)->widget();
    }
}


void MainWindow::on_novoAvistamento_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    for(size_t i = 0; i < v_astros.size(); i++){
        ui->astro1->addItem(QString::fromStdString(v_astros.at(i)->GetName()), QVariant::fromValue(v_astros.at(i)));
    }
    for(size_t i = 0; i < v_locais.size(); i++){
        ui->locaisAvist->addItem(QString::fromStdString(v_locais.at(i)->getCidade() + ", "
                                                                + v_locais.at(i)->getEstado() + ", "
                                                                + v_locais.at(i)->getPais() + " - "
                                                                + v_locais.at(i)->getLatitude() + "; "
                                                                + v_locais.at(i)->getLongitude()),
                                 QVariant::fromValue(v_locais.at(i)));
    }
    for(size_t i = 0; i < v_equips.size(); i++){
        ui->equip1->addItem(QString::fromStdString(v_equips.at(i)->getNomeEquip()), QVariant::fromValue(v_equips.at(i)));
    }
}


void MainWindow::on_abrirFeed_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    for(int i = 1; i < nAvists; i++){
        delete v_comboAvist.at(i);
    }
    v_comboAvist.clear();
    v_comboAvist.push_back(ui->avist1);
    for(size_t i = 0; i < v_avists.size(); i++){
        if(v_avists.at(i)->getIdP() == 0)
            ui->avist1->addItem(v_avists.at(i)->getDataAvist().toString("dd/MM/yyyy") + QString::fromStdString(v_avists.at(i)->getLocal()->getCidade() + ", " + v_avists.at(i)->getLocal()->getEstado()), QVariant::fromValue(v_avists.at(i)));
    }
    ui->descPubli->clear();
    FillFeed();
}


void MainWindow::on_equipamentos_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->tabelaEquips->clearContents();
    ui->tabelaEquips->setRowCount(0);
    for(size_t i = 0; i < v_equips.size(); i++){
        ui->tabelaEquips->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_equips.at(i)->getIdEquip()))
             << QString::fromStdString(v_equips.at(i)->getNomeEquip())
             << QString::fromStdString(v_equips.at(i)->getMarcaEquip())
             << QString::fromStdString(v_equips.at(i)->getEspecEquip())
             << QString::fromStdString(v_equips.at(i)->getTipoEquip()->getDescTipoEquip());
        for(size_t j = 0; j < 5; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tabelaEquips->setItem(i,j,item);
        }
    }
    for(size_t i = 0; i < v_tipo_equip.size(); i++){
        ui->tiposEquip->addItem(QString::fromStdString(v_tipo_equip.at(i)->getDescTipoEquip()), QVariant::fromValue(v_tipo_equip.at(i)));
    }
}


void MainWindow::on_listaAvistamentos_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tabelaAvists->clearContents();
    ui->tabelaAvists->setRowCount(0);
    for(size_t i = 0; i < v_avists.size(); i++){
        ui->tabelaAvists->insertRow(i);
        QStringList data;
        data << QString::fromStdString(to_string(v_avists.at(i)->getIdAvistamento()))
             << QString::fromStdString(v_avists.at(i)->getLocal()->getCidade() + ", " + v_avists.at(i)->getLocal()->getEstado() + ", " + v_avists.at(i)->getLocal()->getPais())
             << v_avists.at(i)->getDataAvist().toString("dd/MM/yyyy");
        QString astros = "";
        for(size_t j = 0; j < v_avists.at(i)->getAstros().size(); j++){
            astros += (QString::fromStdString(v_avists.at(i)->getAstros().at(j)->GetName()) + ", ");
        }
        data << astros;
        QString equips = "";
        for(size_t j = 0; j < v_avists.at(i)->getEquipamentos().size(); j++){
            equips += (QString::fromStdString(v_avists.at(i)->getEquipamentos().at(j)->getNomeEquip()) + ", ");
        }
        data << equips;
        for(size_t j = 0; j < 5; j++){
            QTableWidgetItem *item = new QTableWidgetItem((data.at(j)));
            item->setData(0, QVariant(data.at(j)));
            ui->tabelaAvists->setItem(i,j,item);
        }
    }
}



void MainWindow::on_salvarEquip_clicked()
{
    Equipamento equipamento;
    TipoEquipamento *tipo_equip = ui->tiposEquip->currentData().value<TipoEquipamento*>();
    equipamento.setNomeEquip(ui->nomeEquip->text().toStdString());
    equipamento.setMarcaEquip(ui->marcaEquip->text().toStdString());
    equipamento.setEspecEquip(ui->especEquip->toPlainText().toStdString());
    equipamento.setTipoEquip(tipo_equip);
    if(equipamento.saveEquipamento())
        loadEquipamentos(v_equips, v_tipo_equip);
}




void MainWindow::on_salvarAvistamento_clicked()
{
    Avistamento avist;
    Local *local;
    Astro *astro;
    Equipamento *equip;
    vector<Astro*> astros;
    vector<Equipamento*> equips;
    vector<Imagem> imagens;
    for(int i = 0; i < nEquips; i++){
        equip = v_comboEquip.at(i)->currentData().value<Equipamento*>();
        equips.push_back(equip);
    }
    avist.setEquipamentos(equips);

    for(int i = 0; i < nAstros; i++){
        astro = v_comboAstro.at(i)->currentData().value<Astro*>();
        astros.push_back(astro);
    }

    avist.setAstros(astros);

    local = ui->locaisAvist->currentData().value<Local*>();
    avist.setLocal(local);

    avist.setDataAvist(ui->dataAvistamento->dateTime());

    foreach(QString img, listaImagens){
        Imagem imagem;
        QPixmap qImg;
        qImg.load(img);
        imagem.setImgFile(qImg);
        imagem.setDescImagem("Avistamento na data: " + avist.getDataAvist().toString("dd/MM/yyyy").toStdString());
        imagens.push_back(imagem);

    }
    avist.setImagens(imagens);
    avist.setUsuario(m_usuario);
    ui->dataAvistamento->clear();

    for(int i = 1; i < nEquips; i++){
        delete v_comboEquip.at(i);
    }
    for(int i = 1; i < nAstros; i++){
        delete v_comboAstro.at(i);
    }
    v_comboEquip.clear();
    v_comboAstro.clear();
    nEquips = 1;
    nAstros = 1;

    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(avist.saveAvistamento())
        message.setText("Avistamento salvo com sucesso!");
    else
        message.setText("Algo deu errado ao salvar o Avistamento!");
    message.setFixedSize(325,100);
    message.exec();

    for(int i = 1; i < nAstros; i++){
        delete v_comboAstro.at(i);
    }
    for(size_t i = 0; i < v_astros.size(); i++){
        ui->astro1->addItem(QString::fromStdString(v_astros.at(i)->GetName()), QVariant::fromValue(v_astros.at(i)));
    }
    v_comboAstro.clear();
    v_comboAvist.push_back(ui->astro1);
    for(int i = 1; i < nEquips; i++){
        delete v_comboEquip.at(i);
    }
    for(size_t i = 0; i < v_equips.size(); i++){
        ui->equip1->addItem(QString::fromStdString(v_equips.at(i)->getNomeEquip()), QVariant::fromValue(v_equips.at(i)));
    }
    v_comboEquip.clear();
    v_comboEquip.push_back(ui->equip1);
    ui->listadeImagens->clear();
    loadAvistamentos(v_avists, m_usuario, v_locais);
}


void MainWindow::on_maisAvists_clicked()
{
    nAvists++;
    FillAvistsComboBox();
}


void MainWindow::on_menosAvists_clicked()
{
    nAvists--;
    if(nAvists > 0){
        v_comboAvist.erase(v_comboAvist.begin()+nAvists - 1);
        delete ui->avistPubli->itemAt(nAvists - 1)->widget();
    }
}




void MainWindow::on_enviarPubli_clicked()
{
    Publicacao publi;
    vector<Avistamento*> m_v_avists;

    publi.setDescPubli(ui->descPubli->toPlainText().toStdString());
    for(int i = 0; i < nAvists; i++){
        Avistamento *avistamento;
        avistamento = v_comboAvist.at(i)->currentData().value<Avistamento*>();
        m_v_avists.push_back(avistamento);
    }
    publi.setAvistamentos(m_v_avists);
    publi.setDataPubli(QDateTime::currentDateTime());
    publi.setIsPublic(true);
    QMessageBox message(ui->centralwidget);
    message.addButton(QMessageBox::Ok);
    if(publi.SavePublicacao())
        message.setText("Publicação feita com sucesso!");
    else
        message.setText("Algo deu errado ao fazer a publicação!");
    message.setFixedSize(325,100);
    message.exec();

    for(int i = 1; i < nAvists; i++){
        delete v_comboAvist.at(i);
    }
    loadAvistamentos(v_avists, m_usuario, v_locais);
    for(size_t i = 0; i < v_avists.size(); i++){
        if(v_avists.at(i)->getIdP() == 0)
            ui->avist1->addItem(v_avists.at(i)->getDataAvist().toString("dd/MM/yyyy") + QString::fromStdString(v_avists.at(i)->getLocal()->getCidade() + ", " + v_avists.at(i)->getLocal()->getEstado()), QVariant::fromValue(v_avists.at(i)));
    }
    v_comboAvist.clear();
    v_comboAvist.push_back(ui->avist1);
    ui->descPubli->clear();
    LoadPublicacoes(v_publis, v_locais);
    FillFeed();
}

