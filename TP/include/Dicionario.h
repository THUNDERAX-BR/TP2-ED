#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "Usuario.h"
#include "Tema.h"
#include "Grafo.h"

class Dicionario {
    private:
        int maxUsuarios;
        int maxTemas;
        Usuario** usuarios;
        Tema** temas;
        int* nosUsuarioGrafoSocial;
        int* nosUsuarioGrafoTemas;
        int* nosTemaGrafoTemas;
        int* idsNosGrafoSocial;
        int* idsNosGrafoTemas;
        int numeroUsuarios;
        int numeroTemas;
        //Aumenta o tamanho dos vetores de usuarios quando o numero atinge o maximo
        void expandirVetoresUsuarios();
        //Aumenta o tamanho dos vetores de temas quando o numero atinge o maximo
        void expandirVetoresTemas();
    public:
        //Cria um objeto dicionario, alocando os vetores
        Dicionario();
        //Deleta os vetores
        ~Dicionario();
        //Cria o usuario e o adiciona aos vetores e retorna seu id
        int adicionarUsuario(std::string nome, int idade, Grafo* grafoSocial, Grafo* grafoTemas);
        //Cria o tema e o adiciona aos vetores e retorna seu id
        int adicionarTema(std::string nome, char tipo, Grafo* grafoTemas);
        //Obtem referencia para o usuario informado
        Usuario* obterUsuario(int id);
        //Obtem referencia para o tema informado
        Tema* obterTema(int id);
        //Obtem indice do no do usuario informado no grafo social
        int obterNoUsuarioGrafoSocial(int id);
        //Obtem indice do no do usuario informado no grafo de temas
        int obterNoUsuarioGrafoTemas(int id);
        //Obtem indice do no do tema informado no grafo de temas
        int obterNoTemaGrafoTemas(int id);
        //Obtem id associado ao indice do no do grafo social informado
        int obterIdNoGrafoSocial(int indice);
        //Obtem id (sem distincao de tipo) associado ao indice do no do grafo de temas informado
        int obterIdNoGrafoTemas(int indice);
};

#endif