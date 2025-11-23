#include "../include/BTree.hpp" // Conecta com o header

// --- Implementação do Nó ---
bTreeNode::bTreeNode(int t, bool isLeaf)
{
    this->t = t;
    this->isLeaf = isLeaf;
    keys.reserve(MaxKeys());
    children.reserve(2 * t);
}

// --- Implementação da Árvore ---

bTree::bTree(int t)
{
    this->t = t;
    root = new bTreeNode(t, true);
}

void bTree::insert(int key)
{
    if(root->keys.size() == root->MaxKeys()){
        bTreeNode* newRoot = new bTreeNode(t, false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        int i = 0;
        if(newRoot->keys[0] < key){
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        root = newRoot;
    }else{
        insertNonFull(root, key);
    }
}

void bTree::insertNonFull(bTreeNode* node, int key)
{
    int i = node->keys.size() - 1;
    if(node->isLeaf){
        while(i >= 0 && key < node->keys[i]){
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, key);
    }else{
        while(i >= 0 && key < node->keys[i]){
            i--;
        }
        i++;
        if(node->children[i]->keys.size() == node->children[i]->MaxKeys()){
            splitChild(node, i);
            if(key > node->keys[i]){
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void bTree::splitChild(bTreeNode* parent, int index)
{
    bTreeNode* child = parent->children[index];
    bTreeNode* newChild = new bTreeNode(t, child->isLeaf);

    int mid = child->MiddleKey();
    int origKeys = (int)child->keys.size();
    int origChildren = (int)child->children.size();
    int middleKey = child->keys[mid];

    // 1) Copiar chaves
    for (int i = mid + 1; i < origKeys; ++i) {
        newChild->keys.push_back(child->keys[i]);
    }

    // 2) Copiar filhos (se não for folha)
    if (!child->isLeaf) {
        for (int i = mid + 1; i < origChildren; ++i) {
            newChild->children.push_back(child->children[i]);
        }
    }

    // 3) Reduzir tamanho do filho original
    child->keys.resize(mid);
    if (!child->isLeaf) {
        child->children.resize(mid + 1);
    }

    // 4) Subir a chave mediana para o pai
    parent->keys.insert(parent->keys.begin() + index, middleKey);

    // 5) Conectar o novo filho no pai
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

void bTree::traverse() { traverseNode(root); }

void bTree::traverseNode(bTreeNode* node)
{
    if(node != nullptr){
        int numKeys = node->keys.size();
        for(int i = 0; i < numKeys; i++){
            if(!node->isLeaf) traverseNode(node->children[i]);
            std::cout << node->keys[i] << " ";
        }
        if(!node->isLeaf) traverseNode(node->children[numKeys]);
    }
}

// Implementação do Search privado
bTreeNode* bTree::searchNode(bTreeNode* node, int key)
{
    if(node == nullptr) return nullptr;

    int i = 0;
    while (i < node->keys.size() && key > node->keys[i])
        i++;

    if(i < node->keys.size() && node->keys[i] == key)
        return node;

    if(node->isLeaf) return nullptr;

    return searchNode(node->children[i], key);
}

// Wrapper público para o Search
bool bTree::search(int key) {
    return searchNode(root, key) != nullptr;
}

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