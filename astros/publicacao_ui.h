#ifndef PUBLICACAO_UI_H
#define PUBLICACAO_UI_H

#include <QWidget>
#include "publicacao.h"

namespace Ui {
class Publicacao_ui;
}

class Publicacao_ui : public QWidget
{
    Q_OBJECT

public:
    explicit Publicacao_ui(Publicacao &publi, QWidget *parent = nullptr);
    ~Publicacao_ui();

private:
    Ui::Publicacao_ui *ui;

    Publicacao m_publi;
};

#endif // PUBLICACAO_UI_H
