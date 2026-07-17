#include "Tema.h"
#include <stdexcept>

Tema::Tema(int id, std::string nome, char tipo) : id(id), nome(nome) {
    if (tipo == 'A' || tipo == 'P'){
        this->tipo = tipo;
    } else {
        throw std::invalid_argument("Tipo de tema invalido!");
    }
}

int Tema::getId() {
    return id;
}

std::string Tema::getNome() {
    return nome;
}

char Tema::getTipo() {
    return tipo;
}