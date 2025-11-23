// playground.cpp
// Programa de demonstração e testes básicos da implementação da B-Tree.
// Este ficheiro contém uma implementação completa (standalone) da B-Tree
// seguida por um main que insere alguns números aleatórios e imprime a árvore.

#include <iostream>
#include <random>
#include <vector>

// Estrutura do nó (duplicada aqui para que o playground seja standalone)
struct bTreeNode
{
    std::vector<int> keys;
    std::vector<bTreeNode*> children;
    bool isLeaf;
    int t;
    int MaxKeys() const { return 2 * t - 1; }
    int MiddleKey() const { return t - 1; }

public:
    bTreeNode(int t, bool isLeaf)
    {
        this->t = t;
        this->isLeaf = isLeaf;

        // Reservamos capacidade para melhorar performance nas inserções
        keys.reserve(MaxKeys());
        children.reserve(2 * t);
    }
};

// Classe B-Tree (implementação mínima, igual à usada no código principal)
class bTree
{
    bTreeNode* root;
    int t;
    bTreeNode* searchNode(bTreeNode* node, int key);

public:
    bTree(int t)
    {
        this->t = t;
        root = new bTreeNode(t, true);
    }
    void insert(int key);
    void printTree();
    void traverse();

private:
    void traverseNode(bTreeNode* node);
    void insertNonFull(bTreeNode* node, int key);
    void printTreeNode(bTreeNode* node, int level);
    void splitChild(bTreeNode* parent, int index);
};

// ---------- Implementações ----------

// Insere uma chave na árvore; trata crescimento da altura quando a raiz está cheia
void bTree::insert(int key)
{
    if (root->keys.size() == root->MaxKeys()) {
        bTreeNode* newRoot = new bTreeNode(t, false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        int i = 0;
        if (newRoot->keys[0] < key) {
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        root = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

// Insere em nó não cheio (comportamento comum usado pela B-Tree)
void bTree::insertNonFull(bTreeNode* node, int key)
{
    if (node->isLeaf) {
        int i = (int)node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
    } else {
        int i = (int)node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == node->children[i]->MaxKeys()) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}


// Divide um filho cheio em dois e sobe a chave mediana para o pai
void bTree::splitChild(bTreeNode* parent, int index)
{
    bTreeNode* child = parent->children[index];
    bTreeNode* newChild = new bTreeNode(t, child->isLeaf);

    int mid = child->MiddleKey();
    int origKeys = (int)child->keys.size();
    int origChildren = (int)child->children.size();

    int middleKey = child->keys[mid];

    // Copia chaves à direita da mediana para o novo filho
    for (int i = mid + 1; i < origKeys; ++i) {
        newChild->keys.push_back(child->keys[i]);
    }

    // Se não for folha, copia também os filhos correspondentes
    if (!child->isLeaf) {
        for (int i = mid + 1; i < origChildren; ++i) {
            newChild->children.push_back(child->children[i]);
        }
    }

    // Reduz o tamanho do filho original (esquerdo)
    child->keys.resize(mid);
    if (!child->isLeaf) {
        child->children.resize(mid + 1);
    }

    parent->keys.insert(parent->keys.begin() + index, middleKey);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

void bTree::traverse()
{
    traverseNode(root);
}

void bTree::traverseNode(bTreeNode* node)
{
    if (node != nullptr) {
        int numKeys = (int)node->keys.size();
        for (int i = 0; i < numKeys; i++) {
            if (!node->isLeaf) {
                traverseNode(node->children[i]);
            }
            std::cout << node->keys[i] << " ";
        }

        if (!node->isLeaf) {
            traverseNode(node->children[numKeys]);
        }
    }
}

// Busca recursiva: retorna o nó que contém a chave, ou nullptr
bTreeNode* bTree::searchNode(bTreeNode* node, int key)
{
    if (node == nullptr) {
        return nullptr;
    }

    int i = 0;
    while (i < (int)node->keys.size() && key > node->keys[i])
        i++;

    if (i < (int)node->keys.size() && node->keys[i] == key)
        return node;

    if (node->isLeaf)
        return nullptr;

    return searchNode(node->children[i], key);
}

void bTree::printTree()
{
    printTreeNode(root, 0);
}

void bTree::printTreeNode(bTreeNode* node, int level)
{
    if (node == nullptr) return;

    // imprime indentação por nível
    for (int i = 0; i < level; i++)
        std::cout << "  ";

    // imprime todas as chaves do node
    std::cout << "[ ";
    for (int k : node->keys)
        std::cout << k << " ";
    std::cout << "]\n";

    // se não for folha → imprime filhos
    if (!node->isLeaf) {
        for (bTreeNode* child : node->children)
            printTreeNode(child, level + 1);
    }
}


int main()
{
    // Exemplo simples: grau mínimo 3, insere 20 valores aleatórios e imprime
    bTree tree(3);  // grau mínimo t = 3

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-20, 20);

    for (int i = 0; i < 20; i++) {
        int num = dist(rng);
        std::cout << "Inserting: " << num << std::endl;
        tree.insert(num);
    }

    tree.printTree();
    std::cout << "Traversal of the constructed tree is: ";
    tree.traverse();
    std::cout << std::endl;

    return 0;
}
