// BTree.hpp
// Interface pública da implementação da B-Tree usada no projeto.
// Basicamente esse arquivo declara as classes do projeto.

#pragma once // Garante que o arquivo só seja lido uma vez
#include "includes.hpp"

// Estrutura do nó da B-Tree
// Cada nó contém um vetor de chaves inteiras e um vetor de ponteiros para
// filhos (children). isLeaf indica se o nó é folha. 't' é o grau mínimo.
struct bTreeNode
{
    std::vector<int> keys;                // chaves armazenadas no nó
    std::vector<bTreeNode*> children;     // ponteiros para filhos
    bool isLeaf;                          // indica nó folha
    int t;                                // grau mínimo

    // Helpers para facilitar a leitura/implementação
    // MaxKeys: número máximo de chaves que um nó pode ter (2*t - 1)
    int MaxKeys() const { return 2 * t - 1; }

    // MiddleKey: índice da chave mediana que sobe para o pai quando dividimos
    int MiddleKey() const { return t - 1; }

    bTreeNode(int t, bool isLeaf);
};

// Classe que representa a B-Tree
// API mínima: insert, traverse, search e printTree.
class bTree
{
private:
    bTreeNode* root; // ponteiro para a raiz
    int t;           // grau mínimo da árvore

    // Métodos internos usados pela implementação
    void traverseNode(bTreeNode* node);                // travessia recursiva
    void insertNonFull(bTreeNode* node, int key);      // insere em nó não cheio
    void splitChild(bTreeNode* parent, int index);     // divide filho cheio
    bTreeNode* searchNode(bTreeNode* node, int key);   // busca recursiva
    void printTreeNode(bTreeNode* node, int level);    // impressão com indentação

public:
    bTree(int t); // Construtor: inicializa a árvore com grau mínimo t

    // Métodos públicos (API do usuário / do exemplo)
    void insert(int key);    // insere uma chave na árvore
    void traverse();         // percorre e imprime todas as chaves em ordem
    bool search(int key);    // retorna true se a chave existir
    void printTree();        // imprime estrutura da árvore (níveis)
};