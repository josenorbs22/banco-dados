#ifndef LOCAL_UI_H
#define LOCAL_UI_H

#include <QMainWindow>
#include <vector>
#include "local.h"

namespace Ui {
class Local_ui;
}

class Local_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Local_ui(std::vector<Local*> &l_locais, QWidget *parent = nullptr);
    ~Local_ui();

private slots:
    void on_salvarLocal_clicked();


    void on_cancelar_clicked();

private:
    Ui::Local_ui *ui;
    std::vector<Local*> m_v_locais;
};

#endif // LOCAL_UI_H
