#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include "astro.hpp"
#include "star.hpp"
#include "comet.hpp"
#include "solar-system.hpp"
#include "planet.hpp"
#include "avistamento.h"
#include "equipamento.h"
#include "imagem.h"
#include "local.h"
#include "local_ui.h"
#include "publicacao.h"
#include "tipoequipamento.h"
#include "publicacao_ui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Usuario* usuario, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listaAstros_clicked();

    void on_novoAstro_clicked();

    void on_novoSistemaSolar_clicked();

    void on_listaSistemaSolares_clicked();

    void on_tipoAstro_currentIndexChanged(int index);

    void on_tipoAstroLista_currentIndexChanged(int index);

    void on_morePlanet_2_clicked();

    void on_moreStar_2_clicked();

    void on_removePlanet_2_clicked();

    void on_removeStar_2_clicked();

    void on_saveAstro_clicked();

    void on_deleteAstro_clicked();

    void on_saveSSystem_clicked();

    void on_pushButton_clicked();

    void on_editAstro_clicked();

    void on_actionFoto_triggered();

    void on_selImagens_clicked();

    void on_novoLocal_clicked();

    void on_maisAstros_clicked();

    void on_menosAstros_clicked();

    void on_maisEquip_clicked();

    void on_menosEquip_clicked();

    void on_novoAvistamento_clicked();

    void on_abrirFeed_clicked();

    void on_equipamentos_clicked();

    void on_listaAvistamentos_clicked();

    void on_salvarEquip_clicked();


    void on_salvarAvistamento_clicked();

    void on_maisAvists_clicked();

    void on_menosAvists_clicked();

    void on_enviarPubli_clicked();

private:
    Ui::MainWindow *ui;
    int iPlanets = 1;
    int iStars = 1;
    int nAstros = 1;
    int nEquips = 1;
    int nAvists = 1;
    Usuario* m_usuario;
    std::vector<QComboBox*> v_comboPlanet;
    std::vector<QComboBox*> v_comboStar;
    std::vector<QComboBox*> v_comboAstro;
    std::vector<QComboBox*> v_comboEquip;
    std::vector<QComboBox*> v_comboAvist;
    std::vector<Publicacao_ui*> v_widgetsPubli;
    vector<Star*> v_stars;
    vector<Planet*> v_planets;
    vector<Comet*> v_comets;
    vector<Astro*> v_astros;
    vector<SolarSystem> v_ssystems;
    vector<Avistamento*> v_avists;
    vector<Equipamento*> v_equips;
    vector<Imagem> v_imagens;
    vector<Local*> v_locais;
    vector<Publicacao> v_publis;
    vector<TipoEquipamento*> v_tipo_equip;
    QStringList listaImagens;
    size_t idAstro, idSSystem;
    bool isEditing;
    void FillPlanetsComboBox();
    void FillStarsComboBox();
    void FillAstrosComboBox();
    void FillLocaisComboBox();
    void FillEquipsComboBox();
    void FillAvistsComboBox();
    void FillFeed();
};
#endif // MAINWINDOW_H
