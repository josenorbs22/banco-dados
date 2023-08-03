#include "publicacao_ui.h"
#include "ui_publicacao_ui.h"

Publicacao_ui::Publicacao_ui(Publicacao &publi, QWidget *parent) :
    m_publi(publi), QWidget(parent),
    ui(new Ui::Publicacao_ui)
{
    ui->setupUi(this);
    ui->nomeUsuario->setText(QString::fromStdString(m_publi.getAvistamentos().at(0)->getUsuario()->getNomeUsuario()));
    ui->dataP->setText(m_publi.getDataPubli().toString("dd/MM/yyyy hh:mm"));
    ui->descP->setText(QString::fromStdString(m_publi.getDescPubli()));
    for(size_t i = 0; i < m_publi.getAvistamentos().size(); i++){
        for(size_t j = 0; i < m_publi.getAvistamentos().at(i)->getImagens().size(); i++){
            QLabel *label = new QLabel();
            label->setPixmap(m_publi.getAvistamentos().at(i)->getImagens().at(j).getImgFile());
            ui->imgsPubli->addWidget(label);
        }
    }
}

Publicacao_ui::~Publicacao_ui()
{
    delete ui;
}
