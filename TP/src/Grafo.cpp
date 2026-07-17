#include "Grafo.h"
#include <stdexcept>

Grafo::Grafo(char modo, bool direcionado) : direcionado(direcionado) {

    validarModo(modo);

    this->modo = modo;

    max = 100;
    numeroVertices = 0;

    verticesAdj = nullptr;
    verticesAdjInv = nullptr;
    tamanhosAdj = nullptr;
    tamanhosAdjInv = nullptr;

    matriz = nullptr;

    linhas = nullptr;
    colunas = nullptr;
    numeroArestasCSR = 0;

    bufferAdj = new int[max];
    bufferAdjInv = new int[max];

    if (modo == 'L') {
        //Lista
        verticesAdj = new int *[max];
        tamanhosAdj = new int[max];

        for (int i = 0; i < max; i++) {
            verticesAdj[i] = nullptr;
            tamanhosAdj[i] = 0;
        }

        if (direcionado) {
            verticesAdjInv = new int *[max];
            tamanhosAdjInv = new int[max];

            for (int i = 0; i < max; i++) {
                verticesAdjInv[i] = nullptr;
                tamanhosAdjInv[i] = 0;
            }
        }
    } else if (modo == 'M') {
        //Matriz
        matriz = new bool *[max];

        for (int i = 0; i < max; i++) {
            matriz[i] = new bool[max];

            for (int j = 0; j < max; j++) {
                matriz[i][j] = false;
            }
        }
    } else {
        //CSR
        linhas = new int[max + 1];

        for (int i = 0; i <= max; i++) {
            linhas[i] = 0;
        }

        colunas = new int[1];
    }
}

Grafo::~Grafo() {
    destruirLista();
    destruirMatriz();
    destruirCSR();
    delete[] bufferAdj;
    delete[] bufferAdjInv;
}

void Grafo::validarVertice(int vertice) {
    if (vertice < 0 || vertice >= numeroVertices) {
        throw std::runtime_error("Vertice invalido.");
    }
}

void Grafo::validarModo(char modo) {
    if (modo != 'L' && modo != 'M' && modo != 'C') {
        throw std::runtime_error("Modo invalido.");
    }
}

void Grafo::expandir() {
    int novoMax = max * 2;

    if (modo == 'L') {
        //Lista
        int **novoAdj = new int *[novoMax];
        int *novosTamAdj = new int[novoMax];

        for (int i = 0; i < numeroVertices; i++) {
            novoAdj[i] = verticesAdj[i];
            novosTamAdj[i] = tamanhosAdj[i];
        }

        for (int i = numeroVertices; i < novoMax; i++) {
            novoAdj[i] = nullptr;
            novosTamAdj[i] = 0;
        }

        delete[] verticesAdj;
        delete[] tamanhosAdj;

        verticesAdj = novoAdj;
        tamanhosAdj = novosTamAdj;

        if (direcionado) {
            int **novoAdjInv = new int *[novoMax];
            int *novosTamAdjInv = new int[novoMax];

            for (int i = 0; i < numeroVertices; i++) {
                novoAdjInv[i] = verticesAdjInv[i];
                novosTamAdjInv[i] = tamanhosAdjInv[i];
            }

            for (int i = numeroVertices; i < novoMax; i++) {
                novoAdjInv[i] = nullptr;
                novosTamAdjInv[i] = 0;
            }

            delete[] verticesAdjInv;
            delete[] tamanhosAdjInv;

            verticesAdjInv = novoAdjInv;
            tamanhosAdjInv = novosTamAdjInv;
        }
    } else if (modo == 'M') {
        //Matriz
        bool **novaMatriz = new bool *[novoMax];

        for (int i = 0; i < novoMax; i++) {
            novaMatriz[i] = new bool[novoMax];

            for (int j = 0; j < novoMax; j++) {
                novaMatriz[i][j] = false;
            }
        }

        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                novaMatriz[i][j] = matriz[i][j];
            }
        }

        for (int i = 0; i < max; i++) {
            delete[] matriz[i];
        }

        delete[] matriz;

        matriz = novaMatriz;
    } else {
        //CSR
        int *novasLinhas = new int[novoMax + 1];

        for (int i = 0; i <= numeroVertices; i++) {
            novasLinhas[i] = linhas[i];
        }

        for (int i = numeroVertices + 1; i <= novoMax; i++) {
            novasLinhas[i] = numeroArestasCSR;
        }

        delete[] linhas;

        linhas = novasLinhas;
    }

    max = novoMax;

    delete[] bufferAdj;
    delete[] bufferAdjInv;
    bufferAdj = new int[max];
    bufferAdjInv = new int[max];
}

void Grafo::adicionarArestaLista(int vertice1, int vertice2) {
    //Direto
    int tamanhoAtual = tamanhosAdj[vertice1];
    int pos = 0;

    while (pos < tamanhoAtual && verticesAdj[vertice1][pos] < vertice2) {
        pos++;
    }

    if (pos < tamanhoAtual && verticesAdj[vertice1][pos] == vertice2) {
        //Aresta ja existente
    } else {
        int novoTam = tamanhoAtual + 1;
        int *novaLista = new int[novoTam];

        for (int i = 0; i < pos; i++) {
            novaLista[i] = verticesAdj[vertice1][i];
        }

        novaLista[pos] = vertice2;

        for (int i = pos; i < tamanhoAtual; i++) {
            novaLista[i + 1] = verticesAdj[vertice1][i];
        }

        delete[] verticesAdj[vertice1];

        verticesAdj[vertice1] = novaLista;
        tamanhosAdj[vertice1] = novoTam;
    }

    //Inverso
    if (direcionado) {
        int tamanhoInvAtual = tamanhosAdjInv[vertice2];
        int posInv = 0;

        while (posInv < tamanhoInvAtual && verticesAdjInv[vertice2][posInv] < vertice1) {
            posInv++;
        }

        if (posInv < tamanhoInvAtual && verticesAdjInv[vertice2][posInv] == vertice1) {
            //Aresta inversa ja existente
        } else {
            int novoTamInv = tamanhoInvAtual + 1;
            int *novaListaInv = new int[novoTamInv];

            for (int i = 0; i < posInv; i++) {
                novaListaInv[i] = verticesAdjInv[vertice2][i];
            }

            novaListaInv[posInv] = vertice1;

            for (int i = posInv; i < tamanhoInvAtual; i++) {
                novaListaInv[i + 1] = verticesAdjInv[vertice2][i];
            }

            delete[] verticesAdjInv[vertice2];

            verticesAdjInv[vertice2] = novaListaInv;
            tamanhosAdjInv[vertice2] = novoTamInv;
        }
    }
}

void Grafo::removerArestaLista(int vertice1, int vertice2) {
    int indice = -1;

    for (int i = 0; i < tamanhosAdj[vertice1]; i++) {
        if (verticesAdj[vertice1][i] == vertice2) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        int novoTam = tamanhosAdj[vertice1] - 1;
        int* novaLista = nullptr;

        if (novoTam > 0) {
            novaLista = new int[novoTam];
            int k = 0;

            for (int i = 0; i < tamanhosAdj[vertice1]; i++) {
                if (i != indice) {
                    novaLista[k++] = verticesAdj[vertice1][i];
                }
            }
        }

        delete[] verticesAdj[vertice1];

        verticesAdj[vertice1] = novaLista;
        tamanhosAdj[vertice1] = novoTam;
    }

    //Inverso
    if (direcionado) {
        indice = -1;

        for (int i = 0; i < tamanhosAdjInv[vertice2]; i++) {
            if (verticesAdjInv[vertice2][i] == vertice1) {
                indice = i;
                break;
            }
        }

        if (indice != -1) {
            int novoTam = tamanhosAdjInv[vertice2] - 1;
            int* novaLista = nullptr;

            if (novoTam > 0) {
                novaLista = new int[novoTam];
                int k = 0;

                for (int i = 0; i < tamanhosAdjInv[vertice2]; i++) {
                    if (i != indice) {
                        novaLista[k++] = verticesAdjInv[vertice2][i];
                    }
                }
            }

            delete[] verticesAdjInv[vertice2];

            verticesAdjInv[vertice2] = novaLista;
            tamanhosAdjInv[vertice2] = novoTam;
        }
    }
}

bool Grafo::existeArestaLista(int vertice1, int vertice2) {
    for (int i = 0; i < tamanhosAdj[vertice1]; i++) {
        if (verticesAdj[vertice1][i] == vertice2) {
            return true;
        }
    }

    return false;
}

bool Grafo::existeArestaCSR(int vertice1, int vertice2) {
    int inicio = linhas[vertice1];
    int fim = linhas[vertice1 + 1];

    for (int i = inicio; i < fim; i++) {
        if (colunas[i] == vertice2) {
            return true;
        }
    }

    return false;
}

void Grafo::destruirLista() {
    if (verticesAdj == nullptr) {
        return;
    }

    for (int i = 0; i < numeroVertices; i++) {
        delete[] verticesAdj[i];
    }

    delete[] verticesAdj;
    delete[] tamanhosAdj;

    verticesAdj = nullptr;
    tamanhosAdj = nullptr;

    if (direcionado) {
        for (int i = 0; i < numeroVertices; i++) {
            delete[] verticesAdjInv[i];
        }

        delete[] verticesAdjInv;
        delete[] tamanhosAdjInv;

        verticesAdjInv = nullptr;
        tamanhosAdjInv = nullptr;
    }
}

void Grafo::destruirMatriz() {
    if (matriz == nullptr) {
        return;
    }

    for (int i = 0; i < max; i++) {
        delete[] matriz[i];
    }

    delete[] matriz;

    matriz = nullptr;
}

void Grafo::destruirCSR() {
    if (linhas == nullptr) {
        return;
    }

    delete[] linhas;
    delete[] colunas;

    linhas = nullptr;
    colunas = nullptr;
    numeroArestasCSR = 0;
}

void Grafo::converterParaLista() {
    verticesAdj = new int *[max];
    tamanhosAdj = new int[max];

    for (int i = 0; i < max; i++) {
        verticesAdj[i] = nullptr;
        tamanhosAdj[i] = 0;
    }

    if (direcionado) {
        verticesAdjInv = new int *[max];
        tamanhosAdjInv = new int[max];

        for (int i = 0; i < max; i++) {
            verticesAdjInv[i] = nullptr;
            tamanhosAdjInv[i] = 0;
        }
    }

    if (modo == 'M') {
        //De matriz
        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                if (matriz[i][j]) {
                    adicionarArestaLista(i, j);
                }
            }
        }

        destruirMatriz();
    } else {
        //De CSR
        if (linhas != nullptr && colunas != nullptr) {
            for (int i = 0; i < numeroVertices; i++) {
                int inicio = linhas[i];
                int fim = linhas[i + 1];
                
                if (inicio < 0 || fim < 0 || fim < inicio) {
                    throw std::runtime_error("Indices invalidos nas linhas de CSR!");
                }
                
                for (int j = inicio; j < fim; j++) {
                    if (j < 0 || j >= numeroArestasCSR) {
                        throw std::runtime_error("Acesso fora de limites nas colunas de CSR!");
                    }
                    adicionarArestaLista(i, colunas[j]);
                }
            }
        }

        destruirCSR();
    }

    modo = 'L';
}

void Grafo::converterParaMatriz() {

    matriz = new bool *[max];

    for (int i = 0; i < max; i++) {
        matriz[i] = new bool[max];

        for (int j = 0; j < max; j++) {
            matriz[i][j] = false;
        }
    }

    if (modo == 'L') {
        //De lista
        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < tamanhosAdj[i]; j++) {
                matriz[i][verticesAdj[i][j]] = true;
            }
        }

        destruirLista();
    } else {
        //De CSR
        for (int i = 0; i < numeroVertices; i++) {
            int inicio = linhas[i];
            int fim = linhas[i + 1];

            for (int j = inicio; j < fim; j++) {
                matriz[i][colunas[j]] = true;
            }
        }

        destruirCSR();
    }

    modo = 'M';
}

void Grafo::converterParaCSR() {
    linhas = new int[max + 1];

    int total = 0;

    if (modo == 'L') {
        //De lista
        linhas[0] = 0;

        for (int i = 0; i < numeroVertices; i++) {
            total += tamanhosAdj[i];
            linhas[i + 1] = total;
        }

        for (int i = numeroVertices + 1; i <= max; i++) {
            linhas[i] = total;
        }

        colunas = new int[total];

        int indice = 0;

        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < tamanhosAdj[i]; j++) {
                colunas[indice++] = verticesAdj[i][j];
            }
        }

        destruirLista();
    } else {
        //De matriz
        linhas[0] = 0;

        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                if (matriz[i][j]) {
                    total++;
                }
            }

            linhas[i + 1] = total;
        }

        for (int i = numeroVertices + 1; i <= max; i++) {
            linhas[i] = total;
        }

        colunas = new int[total];

        int indice = 0;

        for (int i = 0; i < numeroVertices; i++) {
            for (int j = 0; j < numeroVertices; j++) {
                if (matriz[i][j]) {
                    colunas[indice++] = j;
                }
            }
        }

        destruirMatriz();
    }

    numeroArestasCSR = total;

    modo = 'C';
}

int Grafo::adicionarVertice() {
    if (numeroVertices == max) {
        expandir();
    }

    numeroVertices++;

    return numeroVertices - 1;
}

void Grafo::adicionarAresta(int vertice1, int vertice2) {
    validarVertice(vertice1);
    validarVertice(vertice2);

    if (modo == 'L') {
        //Lista
        adicionarArestaLista(vertice1, vertice2);

        if (!direcionado) {
            adicionarArestaLista(vertice2, vertice1);
        }
    } else if (modo == 'M') {
        //Matriz
        matriz[vertice1][vertice2] = true;

        if (!direcionado) {
            matriz[vertice2][vertice1] = true;
        }
    } else {
        //CSR
        converterParaLista();
        adicionarAresta(vertice1, vertice2);
        converterParaCSR();
    }
}

void Grafo::removerAresta(int vertice1, int vertice2) {
    validarVertice(vertice1);
    validarVertice(vertice2);

    if (modo == 'L') {
        //Lista
        removerArestaLista(vertice1, vertice2);       

        if (!direcionado) {
            removerArestaLista(vertice2, vertice1);
        }
    } else if (modo == 'M') {
        //Matriz
        matriz[vertice1][vertice2] = false;

        if (!direcionado) {
            matriz[vertice2][vertice1] = false;
        }
    } else {
        //CSR
        converterParaLista();
        removerAresta(vertice1, vertice2);
        converterParaCSR();
    }
}

bool Grafo::existeAresta(int vertice1, int vertice2) {
    validarVertice(vertice1);
    validarVertice(vertice2);

    if (modo == 'L') {
        //Lista
        return existeArestaLista(vertice1, vertice2);
    } else if (modo == 'M') {
        //Matriz
        return matriz[vertice1][vertice2];
    } else {
        //CSR
        return existeArestaCSR(vertice1, vertice2);
    }
}

int* Grafo::obterAdjacentes(int vertice, int& tamanho) {
    validarVertice(vertice);

    if (modo == 'L') {
        //Lista
        tamanho = tamanhosAdj[vertice];

        if (tamanho == 0) {
            return nullptr;
        }

        return verticesAdj[vertice];
    } else if (modo == 'M') {
        //Matriz
        tamanho = 0;

        for (int i = 0; i < numeroVertices; i++) {
            if (matriz[vertice][i]) {
                tamanho++;
            }
        }

        if (tamanho == 0) {
            return nullptr;
        }

        int k = 0;

        for (int i = 0; i < numeroVertices; i++) {
            if (matriz[vertice][i]) {
                bufferAdj[k++] = i;
            }
        }

        return bufferAdj;
    } else {
        //CSR
        int inicio = linhas[vertice];
        int fim = linhas[vertice + 1];

        tamanho = fim - inicio;

        if (tamanho == 0) {
            return nullptr;
        }

        int* inicioPtr = &colunas[linhas[vertice]];
        return inicioPtr;
    }
}

int* Grafo::obterAdjacentesInverso(int vertice, int& tamanho) {
    validarVertice(vertice);

    if (!direcionado) {
        return obterAdjacentes(vertice, tamanho);
    }

    if (modo == 'L') {
        //Lista
        tamanho = tamanhosAdjInv[vertice];

        if (tamanho == 0) {
            return nullptr;
        }

        return verticesAdjInv[vertice];
    } else if (modo == 'M') {
        //Matriz
        tamanho = 0;

        for (int i = 0; i < numeroVertices; i++) {
            if (matriz[i][vertice]) {
                tamanho++;
            }
        }

        if (tamanho == 0) {
            return nullptr;
        }

        int k = 0;

        for (int i = 0; i < numeroVertices; i++) {
            if (matriz[i][vertice]) {
                bufferAdjInv[k++] = i;
            }
        }

        return bufferAdjInv;
    } else {
        //CSR
        tamanho = 0;

        for (int i = 0; i < numeroVertices; i++) {
            int inicio = linhas[i];
            int fim = linhas[i + 1];

            for (int j = inicio; j < fim; j++) {
                if (colunas[j] == vertice) {
                    tamanho++;
                }
            }
        }

        if (tamanho == 0) {
            return nullptr;
        }

        int k = 0;

        for (int i = 0; i < numeroVertices; i++) {
            int inicio = linhas[i];
            int fim = linhas[i + 1];

            for (int j = inicio; j < fim; j++) {
                if (colunas[j] == vertice) {
                    bufferAdjInv[k++] = i;
                }
            }
        }

        return bufferAdjInv;
    }
}

int* Grafo::obterAdjacentesDuplo(int vertice, int& tamanho) {

    validarVertice(vertice);

    if (!direcionado) {
        return obterAdjacentes(vertice, tamanho);
    }

    int tamSaida;
    int tamEntrada;

    int* saida = obterAdjacentes(vertice, tamSaida);
    int* entrada = obterAdjacentesInverso(vertice, tamEntrada);

    if (saida == nullptr || entrada == nullptr) {
        tamanho = 0;
        return nullptr;
    }

    int maxResultado = tamSaida < tamEntrada ? tamSaida : tamEntrada;
    int* resultado = new int[maxResultado];

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < tamSaida && j < tamEntrada) {
        if (saida[i] == entrada[j]) {
            resultado[k++] = saida[i];
            i++;
            j++;
        } else if (saida[i] < entrada[j]) {
            i++;
        } else {
            j++;
        }
    }

    if (k == 0) {
        delete[] resultado;
        tamanho = 0;
        return nullptr;
    }

    tamanho = k;
    return resultado;
}

void Grafo::trocarModo(char modo) {
    validarModo(modo);

    if (modo == this->modo) {
        return;
    }

    if (modo == 'L') {
        converterParaLista();
    } else if (modo == 'M') {
        converterParaMatriz();
    } else {
        converterParaCSR();
    }
}