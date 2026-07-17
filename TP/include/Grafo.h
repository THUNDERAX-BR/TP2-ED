#ifndef GRAFO_H
#define GRAFO_H

class Grafo {
    private:
        char modo;
        bool direcionado;
        int max;
        int numeroVertices;

        //Lista de adjacencia
        int** verticesAdj;
        //Lista de adjacencia inversa, usada apenas em grafos direcionados
        int** verticesAdjInv;
        int* tamanhosAdj;
        //Tamanhos da lista inversa, usado apenas em grafos direcionados
        int* tamanhosAdjInv;

        //Matriz de adjacencia
        bool** matriz;

        //Matriz esparsa CSR
        int* linhas;
        int* colunas;
        int numeroArestasCSR;

        //Buffers internos de retorno para obterAdjacentes e obterAdjacentesInverso
        int* bufferAdj;
        int* bufferAdjInv;

        //Lanca excecao se o vertice informado nao existir no grafo
        void validarVertice(int vertice);
        //Lanca excecao se o modo informado for invalido
        void validarModo(char modo);
        //Dobra a capacidade maxima do grafo, realocando todas as estruturas internas
        void expandir();
        //Adiciona aresta na lista de adjacencia, incluindo a lista inversa em grafos direcionados
        void adicionarArestaLista(int vertice1, int vertice2);
        //Remove aresta da lista de adjacencia, incluindo a lista inversa em grafos direcionados
        void removerArestaLista(int vertice1, int vertice2);
        //Verifica a existencia de aresta na lista de adjacencia
        bool existeArestaLista(int vertice1, int vertice2);
        //Verifica a existencia de aresta na matriz esparsa CSR
        bool existeArestaCSR(int vertice1, int vertice2);
        //Libera toda a memoria ocupada pela lista de adjacencia
        void destruirLista();
        //Libera toda a memoria ocupada pela matriz de adjacencia
        void destruirMatriz();
        //Libera toda a memoria ocupada pela matriz esparsa CSR
        void destruirCSR();
        //Converte a representacao atual para lista de adjacencia e atualiza o modo
        void converterParaLista();
        //Converte a representacao atual para matriz de adjacencia e atualiza o modo
        void converterParaMatriz();
        //Converte a representacao atual para matriz esparsa CSR e atualiza o modo
        void converterParaCSR();
    public:
        //Cria um grafo vazio com o modo de armazenamento selecionado e define se e direcionado
        Grafo(char modo, bool direcionado);
        //Libera toda a memoria alocada pelo grafo
        ~Grafo();
        //Adiciona um vertice ao grafo e retorna seu indice
        int adicionarVertice();
        //Adiciona uma aresta entre os vertices informados, do 1 para o 2 em direcionados,
        //e nos dois sentidos em nao direcionados
        void adicionarAresta(int vertice1, int vertice2);
        //Remove a aresta entre os vertices informados, do 1 para o 2 em direcionados,
        //e nos dois sentidos em nao direcionados
        void removerAresta(int vertice1, int vertice2);
        //Verifica a existencia de aresta entre os vertices informados, do 1 para o 2 em direcionados
        bool existeAresta(int vertice1, int vertice2);
        //Obtem a lista de vertices para os quais o vertice informado possui aresta e atribui o tamanho
        //a variavel passada. O ponteiro retornado nao deve ser deletado pelo chamador
        int* obterAdjacentes(int vertice, int& tamanho);
        //Obtem a lista de vertices que possuem aresta para o vertice informado em grafos direcionados
        //e atribui o tamanho a variavel passada. Equivalente a obterAdjacentes em nao direcionados.
        //O ponteiro retornado nao deve ser deletado pelo chamador
        int* obterAdjacentesInverso(int vertice, int& tamanho);
        //Obtem a lista de vertices que possuem aresta simultaneamente de e para o vertice informado
        //em grafos direcionados e atribui o tamanho a variavel passada. Equivalente a obterAdjacentes
        //em nao direcionados. O ponteiro retornado deve ser deletado pelo chamador
        int* obterAdjacentesDuplo(int vertice, int& tamanho);
        //Troca o modo de armazenamento para o informado, convertendo todos os dados
        void trocarModo(char modo);
};

#endif