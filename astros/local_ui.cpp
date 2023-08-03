#include "local_ui.h"
#include "ui_local_ui.h"

Local_ui::Local_ui(std::vector<Local*> &v_locais, QWidget *parent) :
    m_v_locais(v_locais), QMainWindow(parent),
    ui(new Ui::Local_ui)
{
    ui->setupUi(this);
}

Local_ui::~Local_ui()
{
    delete ui;
}

void Local_ui::on_salvarLocal_clicked()
{
    bool done;
    if(ui->latLocal->text().size() > 0 && ui->longLocal->text().size() > 0){
        Local local;
        local.setCidade(ui->cidadeLocal->text().toStdString());
        local.setEstado(ui->estadoLocal->text().toStdString());
        local.setPais(ui->paisLocal->text().toStdString());
        local.setLatitude(ui->latLocal->text().toStdString());
        local.setLongitude(ui->longLocal->text().toStdString());
        done = local.SaveLocal();
        LoadLocais(m_v_locais);
        if(done){
            this->close();
        }
    }
}


void Local_ui::on_cancelar_clicked()
{
    this->close();
}

