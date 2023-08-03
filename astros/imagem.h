#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include "astro.hpp"

class Imagem {
private:
    int m_id_imagem;
    std::string m_desc_imagem;
    float m_tamanho_imagem;
    QPixmap m_file;

public:
    Imagem();
    int getIdImagem() const{return m_id_imagem;}
    void setIdImagem(int id_imagem) {m_id_imagem = id_imagem;}
    std::string getDescImagem() const{return m_desc_imagem;}
    void setDescImagem(std::string desc_imagem) {m_desc_imagem = desc_imagem;}
    float getTamanhoImagem() const{return m_tamanho_imagem;}
    void setTamanhoImagem(float tamanho_imagem) {m_tamanho_imagem = tamanho_imagem;}
    QPixmap getImgFile() {return m_file;}
    void setImgFile(QPixmap file) {m_file = file;}
};

#endif // IMAGEM_H
