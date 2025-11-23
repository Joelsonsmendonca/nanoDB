#include <iostream>
#include <print>
#include <random>
#include <vector>

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

        keys.reserve(MaxKeys());
        children.reserve(2 * t);
    }
};

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
    if(node->isLeaf){
        int i = node->keys.size() -1;
        while(i >= 0 && key < node->keys[i]){
            i--;
        }
        node->keys.insert(node->keys.begin() + i +1, key);
    }else{
        int i = node->keys.size() -1;
        while(i >=0 && key < node->keys[i]){
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

void bTree::traverse()
{
    traverseNode(root);
}

void bTree::traverseNode(bTreeNode* node)
{
    if(node != nullptr){
        int numKeys = node->keys.size();
        for(int i = 0; i < numKeys; i++){
            if(!node->isLeaf){
                traverseNode(node->children[i]);
            }
            std::cout << node->keys[i] << " ";
        }

        if(!node->isLeaf){
            traverseNode(node->children[numKeys]);
        }
    }
}

bTreeNode* bTree::searchNode(bTreeNode* node, int key)
{
    if(node == nullptr){
        return nullptr;
    }

    int i = 0;
    while (i < node->keys.size() && key > node->keys[i])
        i++;

    if(i < node->keys.size() && node->keys[i] == key)
        return node;

    if(node->isLeaf)
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
    if (!node->isLeaf)
    {
        for (bTreeNode* child : node->children)
            printTreeNode(child, level + 1);
    }
}


int main ()
{
    bTree tree(3);  // grau mínimo t = 3

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);
    tree.printTree();
    std::cout << "Traversal of the constructed tree is: ";
    tree.traverse();
    std::cout << std::endl;
    
    return 0;
}
