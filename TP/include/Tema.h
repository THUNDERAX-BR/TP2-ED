#ifndef TEMA_H
#define TEMA_H

#include <string>

class Tema {
    private:
        int id;
        std::string nome;
        char tipo;
    public:
        //Cria um tema com as informacoes passadas, validando o tipo
        Tema(int id, std::string nome, char tipo);
        //Obtem o id do tema
        int getId();
        //Obtem o nome do tema
        std::string getNome();
        //Obtem ao tipo do tema
        char getTipo();
};

#endif