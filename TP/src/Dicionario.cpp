#include "Dicionario.h"

Dicionario::Dicionario() : maxUsuarios(100), maxTemas(100), numeroUsuarios(0), numeroTemas(0) {
    usuarios = new Usuario*[maxUsuarios];
    temas = new Tema*[maxTemas];
    nosUsuarioGrafoSocial = new int[maxUsuarios];
    nosUsuarioGrafoTemas = new int[maxUsuarios];
    nosTemaGrafoTemas = new int[maxTemas];
    idsNosGrafoSocial = new int[maxUsuarios];
    idsNosGrafoTemas = new int[maxUsuarios + maxTemas];
}

Dicionario::~Dicionario() {
    for (int i = 0; i < numeroUsuarios; i++) {
        delete usuarios[i];
    }
    for (int i = 0; i < numeroTemas; i++) {
        delete temas[i];
    }
    delete[] usuarios;
    delete[] temas;
    delete[] nosUsuarioGrafoSocial;
    delete[] nosUsuarioGrafoTemas;
    delete[] nosTemaGrafoTemas;
    delete[] idsNosGrafoSocial;
    delete[] idsNosGrafoTemas;
}

void Dicionario::expandirVetoresUsuarios() {
    maxUsuarios = maxUsuarios * 2;

    Usuario** novosUsuarios = new Usuario*[maxUsuarios];
    int* novosNosUsuarioGrafoSocial = new int[maxUsuarios];
    int* novosNosUsuarioGrafoTemas = new int[maxUsuarios];
    int* novosIdsNosGrafoSocial = new int[maxUsuarios];
    int* novosIdsNosGrafoTemas = new int[maxUsuarios + maxTemas];

    for (int i = 0; i < numeroUsuarios; i++) {
        novosUsuarios[i] = usuarios[i];
        novosNosUsuarioGrafoSocial[i] = nosUsuarioGrafoSocial[i];
        novosNosUsuarioGrafoTemas[i] = nosUsuarioGrafoTemas[i];
        novosIdsNosGrafoSocial[i] = idsNosGrafoSocial[i];
        novosIdsNosGrafoTemas[i] = idsNosGrafoTemas[i];
    }

    for (int i = numeroUsuarios; i < numeroUsuarios + numeroTemas; i++) {
        novosIdsNosGrafoTemas[i] = idsNosGrafoTemas[i];
    }

    delete[] usuarios;
    delete[] nosUsuarioGrafoSocial;
    delete[] nosUsuarioGrafoTemas;
    delete[] idsNosGrafoSocial;
    delete[] idsNosGrafoTemas;

    usuarios = novosUsuarios;
    nosUsuarioGrafoSocial = novosNosUsuarioGrafoSocial;
    nosUsuarioGrafoTemas = novosNosUsuarioGrafoTemas;
    idsNosGrafoSocial = novosIdsNosGrafoSocial;
    idsNosGrafoTemas = novosIdsNosGrafoTemas;
}

void Dicionario::expandirVetoresTemas() {
    maxTemas = maxTemas * 2;

    Tema** novosTemas = new Tema*[maxTemas];
    int* novosNosTemaGrafoTemas = new int[maxTemas];
    int* novosIdsNosGrafoTemas = new int[maxUsuarios + maxTemas];

    for (int i = 0; i < numeroTemas; i++) {
        novosTemas[i] = temas[i];
        novosNosTemaGrafoTemas[i] = nosTemaGrafoTemas[i];
        novosIdsNosGrafoTemas[i] = idsNosGrafoTemas[i];
    }

    for (int i = 0; i < numeroUsuarios; i++) {
        novosIdsNosGrafoTemas[i] = idsNosGrafoTemas[i];
    }

    delete[] temas;
    delete[] nosTemaGrafoTemas;
    delete[] idsNosGrafoTemas;

    temas = novosTemas;
    nosTemaGrafoTemas = novosNosTemaGrafoTemas;
    idsNosGrafoTemas = novosIdsNosGrafoTemas;
}

int Dicionario::adicionarUsuario(std::string nome, int idade, Grafo* grafoSocial, Grafo* grafoTemas) {
    Usuario* usuario = new Usuario(numeroUsuarios, nome, idade);

    if (numeroUsuarios + 1 == maxUsuarios) {
        expandirVetoresUsuarios();
    }

    usuarios[numeroUsuarios] = usuario;
    nosUsuarioGrafoSocial[numeroUsuarios] = grafoSocial->adicionarVertice();
    nosUsuarioGrafoTemas[numeroUsuarios] = grafoTemas->adicionarVertice();
    idsNosGrafoSocial[nosUsuarioGrafoSocial[numeroUsuarios]] = numeroUsuarios;
    idsNosGrafoTemas[nosUsuarioGrafoTemas[numeroUsuarios]] = numeroUsuarios;
    numeroUsuarios++;

    return usuario->getId();
}

int Dicionario::adicionarTema(std::string nome, char tipo, Grafo* grafoTemas) {
    Tema* tema = new Tema(numeroTemas, nome, tipo);

    if (numeroTemas + 1 == maxTemas) {
        expandirVetoresTemas();
    }

    temas[numeroTemas] = tema;
    nosTemaGrafoTemas[numeroTemas] = grafoTemas->adicionarVertice();
    idsNosGrafoTemas[nosTemaGrafoTemas[numeroTemas]] = numeroTemas;
    numeroTemas++;

    return tema->getId();
}

Usuario* Dicionario::obterUsuario(int id) {
    return usuarios[id];
}

Tema* Dicionario::obterTema(int id) {
    return temas[id];
}

int Dicionario::obterNoUsuarioGrafoSocial(int id) {
    return nosUsuarioGrafoSocial[id];
}

int Dicionario::obterNoUsuarioGrafoTemas(int id) {
    return nosUsuarioGrafoTemas[id];
}

int Dicionario::obterNoTemaGrafoTemas(int id) {
    return nosTemaGrafoTemas[id];
}

int Dicionario::obterIdNoGrafoSocial(int indice) {
    return idsNosGrafoSocial[indice];
}

int Dicionario::obterIdNoGrafoTemas(int indice) {
    return idsNosGrafoTemas[indice];
}