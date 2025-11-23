#pragma once // Garante que o arquivo só seja lido uma vez
#include "includes.hpp"


// Estrutura do Nó
struct bTreeNode
{
    std::vector<int> keys;
    std::vector<bTreeNode*> children; // Ainda usando ponteiros por enquanto (memória)
    bool isLeaf;
    int t; // Grau mínimo

    // Helpers para facilitar a leitura
    int MaxKeys() const { return 2 * t - 1; }
    int MiddleKey() const { return t - 1; }  

    bTreeNode(int t, bool isLeaf);
};

// Classe da Árvore
class bTree
{
private:
    bTreeNode* root;
    int t;

    // Métodos internos (privados)
    void traverseNode(bTreeNode* node);
    void insertNonFull(bTreeNode* node, int key);
    void splitChild(bTreeNode* parent, int index);
    bTreeNode* searchNode(bTreeNode* node, int key);
    void printTreeNode(bTreeNode* node, int level);

public:
    bTree(int t); // Construtor

    // Métodos públicos (API do usuário)
    void insert(int key);
    void traverse();
    bool search(int key); // Wrapper simples para o searchNode
    void printTree();     // Visualização
};