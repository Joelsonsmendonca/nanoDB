// Esse arquivo basicamente contém a "bagunça" da implementação das classes.
#include "../include/BTree.hpp" // inclui a declaração das classes

// --- Implementação do Nó ---
// O construtor apenas inicializa os campos e faz reserve() nos vetores para
// reduzir realocações dinâmicas durante inserções.
bTreeNode::bTreeNode(int t, bool isLeaf)
{
    this->t = t;
    this->isLeaf = isLeaf;
    // Reserva capacidade para evitar realocações frequentes
    keys.reserve(MaxKeys());
    children.reserve(2 * t);
}

// --- Implementação da Árvore ---

// Construtor da árvore: cria uma raiz vazia (folha)
bTree::bTree(int t)
{
    this->t = t;
    root = new bTreeNode(t, true);
}

// Inserção pública: trata o caso especial em que a raiz está cheia e precisa
// ser dividida (a árvore cresce em altura), ou encaminha para insertNonFull.
void bTree::insert(int key)
{
    if (root->keys.size() == root->MaxKeys()) {
        // raiz cheia: criamos uma nova raiz e dividimos o antigo root
        bTreeNode* newRoot = new bTreeNode(t, false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);

        int i = 0;
        // seleciona o filho correto após a divisão
        if (newRoot->keys[0] < key) {
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        root = newRoot; // atualiza a raiz
    } else {
        // raiz não cheia: insere diretamente
        insertNonFull(root, key);
    }
}

// Insere uma chave em um nó que não está cheio. Se o nó for interno, e o
// filho destino estiver cheio, divide o filho antes de descer.
void bTree::insertNonFull(bTreeNode* node, int key)
{
    int i = (int)node->keys.size() - 1;

    if (node->isLeaf) {
        // nó folha: encontra a posição correta e insere deslocando as outras chaves
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
    } else {
        // nó interno: encontra o filho para descer
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // se o filho está cheio, divida-o primeiro
        if (node->children[i]->keys.size() == node->children[i]->MaxKeys()) {
            splitChild(node, i);
            // após split, pode ser necessário selecionar o próximo filho
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// splitChild: divide o filho 'child' do pai na posição 'index' em dois
// nós e sobe a chave mediana para o pai.
void bTree::splitChild(bTreeNode* parent, int index)
{
    bTreeNode* child = parent->children[index];
    bTreeNode* newChild = new bTreeNode(t, child->isLeaf);

    // índice da chave do meio no child
    int mid = child->MiddleKey();

    // guardamos tamanhos originais porque vamos manipular os vetores
    int origKeys = (int)child->keys.size();
    int origChildren = (int)child->children.size();

    // valor que sobe para o parent
    int middleKey = child->keys[mid];

    // 1) copiar as chaves da metade direita para newChild
    for (int i = mid + 1; i < origKeys; ++i) {
        newChild->keys.push_back(child->keys[i]);
    }

    // 2) se não for folha, copiar os pointers filhos correspondentes
    if (!child->isLeaf) {
        // os filhos a copiar começam em mid+1 e vão até origChildren-1
        for (int i = mid + 1; i < origChildren; ++i) {
            newChild->children.push_back(child->children[i]);
        }
    }

    // 3) reduzir o tamanho do child esquerdo: ele deve ficar com as primeiras `mid` chaves
    //    e (se não for folha) com os primeiros (mid+1) filhos
    child->keys.resize(mid);
    if (!child->isLeaf) {
        child->children.resize(mid + 1); // left child keeps mid+1 children
    }

    // 4) inserir middleKey no parent na posição correta (index)
    parent->keys.insert(parent->keys.begin() + index, middleKey);

    // 5) inserir newChild como filho imediatamente à direita do child (index + 1)
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

// Funções de travessia e impressão
void bTree::traverse() { traverseNode(root); }

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

// Implementação do Search privado: busca por nó recursivamente
bTreeNode* bTree::searchNode(bTreeNode* node, int key)
{
    if (node == nullptr) return nullptr;

    int i = 0;
    // encontra a primeira posição onde key <= node->keys[i]
    while (i < (int)node->keys.size() && key > node->keys[i])
        i++;

    if (i < (int)node->keys.size() && node->keys[i] == key)
        return node; // encontrou no nó atual

    if (node->isLeaf) return nullptr; // não encontrado

    // desce para o filho apropriado
    return searchNode(node->children[i], key);
}

// Wrapper público para o Search
bool bTree::search(int key) {
    return searchNode(root, key) != nullptr;
}

// Impressão estruturada da árvore: recursiva com nível/indentação
void bTree::printTree() { printTreeNode(root, 0); }

void bTree::printTreeNode(bTreeNode* node, int level)
{
    if (node == nullptr) return;
    for (int i = 0; i < level; i++) std::cout << "  ";
    std::cout << "[ ";
    for (int k : node->keys) std::cout << k << " ";
    std::cout << "]\n";

    if (!node->isLeaf) {
        for (bTreeNode* child : node->children)
            printTreeNode(child, level + 1);
    }
}