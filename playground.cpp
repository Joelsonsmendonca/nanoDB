#include <iostream>
#include <vector>

struct bTreeNode
{
    std::vector<int> keys;
    std::vector<bTreeNode*> children;
    bool isLeaf;
    int t;  

public:
    bTreeNode(int t, bool isLeaf)
    {
        this->t = t;
        this->isLeaf = isLeaf;

        keys.reserve(2 * t -1);
        children.reserve(2 * t);
    }
};

class bTree
{
    bTreeNode* root;
    int t;
    void insert(int key);
    bTreeNode* searchNode(bTreeNode* node, int key);

public:
    bTree(int t)
    {
        this->t = t;
        root = new bTreeNode(t, true);
    }
    void traverse();
private:
    void traverseNode(bTreeNode* node);


    void splitChild(bTreeNode* parent, int index);
};

// ---------- Implementações ----------

void bTree::insert(int key)
{
    // lógica de inserção futura
}

void bTree::splitChild(bTreeNode* parent, int index)
{

    bTreeNode* child = parent->children[index];
    bTreeNode* newChild = new bTreeNode(t, child->isLeaf);

    int mid = t - 1;
    int middleKey = child->keys[mid];

    for(int i = mid + 1; i < child->keys.size(); i++)
    {
     newChild->keys.push_back(child->keys[i]);
    }

    if(!child->isLeaf){
        for(int j = t; j <= child->children.size() -1; j++){
            newChild->children.push_back(child->children[j]);
        }
        newChild->children.resize(t);
    }
    child->keys.resize(mid);
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

int main ()
{
    bTree tree(3);  // grau mínimo t = 3

    // pegar o root diretamente
    bTreeNode* root = new bTreeNode(3, true);
    
    // adicionar chaves manualmente
    root->keys.push_back(10);
    root->keys.push_back(20);
    root->keys.push_back(30);

    // atribuir root à árvore
    tree.traverse(); // para testar a função de travessia

    std::cout << "Traversal of the tree is: " << std::endl;
    
    return 0;
}
