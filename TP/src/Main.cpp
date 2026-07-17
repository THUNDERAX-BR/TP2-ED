#include <exception>
#include <iostream>
#include <sstream>
#include "Dicionario.h"

//Valida se o modo informado existe
void validarModo(char modo) {
    if (modo != 'L' && modo != 'M' && modo != 'C') {
        throw std::runtime_error("Modo invalido no comando A.");
    }
}

//Valida se o tipo de tema existe
void validarTipoTema(char tipo) {
    if (tipo != 'A' && tipo != 'P') {
        throw std::runtime_error("Tipo de tema invalido.");
    }
}

//Garante leitura de um inteiro positivo
void lerPositivo(std::istringstream& iss, int& valor) {
    if (!(iss >> valor) || valor < 0) {
        throw std::runtime_error("Inteiro positivo invalido!");
    }
}

//Garante que a linha nao contenha parametros extras
void exigirFimDaLinha(std::istringstream& iss) {
    std::string extra;

    if (iss >> extra) {
        throw std::runtime_error("Parametros extras na linha!");
    }
}

//Main
int main(int argc, char const *argv[]) {
    try {
        Dicionario dicionario;
        Grafo* grafoSocial;
        Grafo* grafoTemas;

        std::string linha;

        //Lê a primeira linha (deve ser A)
        {
            if (!getline(std::cin, linha)) {
                throw std::runtime_error("Arquivo vazio!");
            }

            std::istringstream iss(linha);
            std::string comando;

            if (!(iss >> comando)) {
                throw std::runtime_error("Erro na linha: Comando ausente na primeira linha!");
            }

            if (comando != "A") {
                throw std::runtime_error("Primeira linha deve ser comando A.");
            }

            char modo;

            if (!(iss >> modo)) {
                throw std::runtime_error("Comando A incompleto.");
            }

            validarModo(modo);
            exigirFimDaLinha(iss);

            grafoSocial = new Grafo(modo, true);
            grafoTemas = new Grafo(modo, false);

            std::cout << "A " << modo;
        }

        //Le as linhas do arquivo
        while (std::getline(std::cin, linha)) {
            if (linha.empty()) {
                continue;
            }

            std::istringstream iss(linha);
            std::string comando;

            if (!(iss >> comando)) {
                std::cerr << "Erro na linha: Comando ausente!" << std::endl;
                continue;
            }

            //Processar comandos
            try{
                if (comando == "A") {
                    char modo;

                    if (!(iss >> modo)) {
                        throw std::runtime_error("Comando A incompleto.");
                    }

                    validarModo(modo);
                    exigirFimDaLinha(iss);

                    grafoSocial->trocarModo(modo);
                    grafoTemas->trocarModo(modo);

                    std::cout << std::endl << "A " << modo;
                } else if (comando == "T") {
                    std::string nomeTema;
                    char tipoTema;

                    if (!(iss >> nomeTema >> tipoTema)) {
                        throw std::runtime_error("Comando T incompleto.");
                    }

                    validarTipoTema(tipoTema);
                    exigirFimDaLinha(iss);

                    std::cout << std::endl << "T " << dicionario.adicionarTema(nomeTema, tipoTema, grafoTemas);
                } else if (comando == "U") {
                    std::string nomeUsuario;
                    int idadeUsuario;

                    if (!(iss >> nomeUsuario)) {
                        throw std::runtime_error("Nome de usuario ausente.");
                    }

                    lerPositivo(iss, idadeUsuario);

                    int id = dicionario.adicionarUsuario(nomeUsuario, idadeUsuario, grafoSocial, grafoTemas);

                    int idTema;

                    while (iss >> idTema) {
                        grafoTemas->adicionarAresta(dicionario.obterNoUsuarioGrafoTemas(id), dicionario.obterNoTemaGrafoTemas(idTema));
                    }

                    std::cout << std::endl << "U " << id;
                } else if (comando == "S") {
                    int id1;
                    int id2;

                    lerPositivo(iss, id1);
                    lerPositivo(iss, id2);
                    exigirFimDaLinha(iss);

                    grafoSocial->adicionarAresta(dicionario.obterNoUsuarioGrafoSocial(id1), dicionario.obterNoUsuarioGrafoSocial(id2));

                    std::cout << std::endl << "S " << dicionario.obterUsuario(id1)->getNome() << " " << dicionario.obterUsuario(id2)->getNome();
                } else if (comando == "R") {
                    int id1;
                    int id2;

                    lerPositivo(iss, id1);
                    lerPositivo(iss, id2);
                    exigirFimDaLinha(iss);

                    grafoSocial->removerAresta(dicionario.obterNoUsuarioGrafoSocial(id1), dicionario.obterNoUsuarioGrafoSocial(id2));

                    std::cout << std::endl << "R " << dicionario.obterUsuario(id1)->getNome() << " " << dicionario.obterUsuario(id2)->getNome();
                } else if (comando == "LT") {
                    int idUsuario;

                    lerPositivo(iss, idUsuario);
                    exigirFimDaLinha(iss);

                    int tamanho;
                    int* indices = grafoTemas->obterAdjacentes(dicionario.obterNoUsuarioGrafoTemas(idUsuario), tamanho);

                    std::cout << std::endl << "LT " << dicionario.obterUsuario(idUsuario)->getNome();

                    for (int i = 0; i < tamanho; i++) {
                        std::cout << " " << dicionario.obterTema(dicionario.obterIdNoGrafoTemas(indices[i]))->getNome();
                    }
                } else if (comando == "LC") {
                    int idUsuario;

                    lerPositivo(iss, idUsuario);
                    exigirFimDaLinha(iss);

                    int tamanho;
                    int* indices = grafoSocial->obterAdjacentesInverso(dicionario.obterNoUsuarioGrafoSocial(idUsuario), tamanho);

                    std::cout << std::endl << "LC " << dicionario.obterUsuario(idUsuario)->getNome();

                    for (int i = 0; i < tamanho; i++) {
                        std::cout << " " << dicionario.obterUsuario(dicionario.obterIdNoGrafoSocial(indices[i]))->getNome();
                    }
                } else if (comando == "LS") {
                    int idUsuario;

                    lerPositivo(iss, idUsuario);
                    exigirFimDaLinha(iss);

                    int tamanho;
                    int* indices = grafoSocial->obterAdjacentes(dicionario.obterNoUsuarioGrafoSocial(idUsuario), tamanho);

                    std::cout << std::endl << "LS " << dicionario.obterUsuario(idUsuario)->getNome();

                    for (int i = 0; i < tamanho; i++) {
                        std::cout << " " << dicionario.obterUsuario(dicionario.obterIdNoGrafoSocial(indices[i]))->getNome();
                    }
                } else if (comando == "LA") {
                    int idUsuario;

                    lerPositivo(iss, idUsuario);
                    exigirFimDaLinha(iss);

                    int tamanho;
                    int* indices = grafoSocial->obterAdjacentesDuplo(dicionario.obterNoUsuarioGrafoSocial(idUsuario), tamanho);

                    std::cout << std::endl << "LA " << dicionario.obterUsuario(idUsuario)->getNome();

                    for (int i = 0; i < tamanho; i++) {
                        std::cout << " " << dicionario.obterUsuario(dicionario.obterIdNoGrafoSocial(indices[i]))->getNome();
                    }

                    if (indices != nullptr) {
                        delete[] indices;
                    }
                } else if (comando == "Q") {
                    int id1;
                    int id2;

                    lerPositivo(iss, id1);
                    lerPositivo(iss, id2);
                    exigirFimDaLinha(iss);

                    bool s12 = grafoSocial->existeAresta(id1, id2);
                    bool s21 = grafoSocial->existeAresta(id2, id1);
                    int relacao = 0;

                    if (s12 && s21) {
                        relacao = 3;
                    } else if (s12) {
                        relacao = 1;
                    } else if (s21) {
                        relacao = 2;
                    }

                    std::cout << std::endl << "Q " << dicionario.obterUsuario(id1)->getNome() << " " << dicionario.obterUsuario(id2)->getNome() << " " << relacao;
                } else if (comando == "G") {
                    int idUsuario;
                    int idTema;

                    lerPositivo(iss, idUsuario);
                    lerPositivo(iss, idTema);
                    exigirFimDaLinha(iss);

                    bool interesse = grafoTemas->existeAresta(dicionario.obterNoUsuarioGrafoTemas(idUsuario), dicionario.obterNoTemaGrafoTemas(idTema));
                    int resultado = 0;

                    if (interesse) {
                        resultado = 1;
                    }

                    std::cout << std::endl << "G " << dicionario.obterUsuario(idUsuario)->getNome() << " " << dicionario.obterTema(idTema)->getNome() << " " << resultado;
                } else if (comando == "F") {
                    int idTema;

                    lerPositivo(iss, idTema);
                    exigirFimDaLinha(iss);

                    int tamanho;
                    grafoTemas->obterAdjacentes(dicionario.obterNoTemaGrafoTemas(idTema), tamanho);

                    std::cout << std::endl << "F " << dicionario.obterTema(idTema)->getNome() << " " << tamanho;
                } else {
                    throw std::runtime_error("Comando invalido.");
                }
            } catch (const std::exception& e) {
                std::cerr << "Erro no comando: " << e.what() << std::endl;
            }
        }

        delete grafoSocial;
        delete grafoTemas;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Erro desconhecido!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}