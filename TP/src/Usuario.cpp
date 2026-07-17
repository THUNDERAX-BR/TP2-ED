#include "Usuario.h"

Usuario::Usuario(int id, std::string nome, int idade) : id(id), nome(nome), idade(idade) {}

int Usuario::getId() {
    return id;
}

std::string Usuario::getNome() {
    return nome;
}

int Usuario::getIdade() {
    return idade;
}