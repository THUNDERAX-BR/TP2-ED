#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
    private:
        int id;
        std::string nome;
        int idade;
    public:
        //Cria um usuario com as informacoes passadas
        Usuario(int id, std::string nome, int idade);
        //Obtem o id do usuario
        int getId();
        //Obtem o nome do usuario
        std::string getNome();
        //Obtem a idade do usuario
        int getIdade();
};

#endif