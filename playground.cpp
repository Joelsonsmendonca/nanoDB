#include <iostream>
#include <print>
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
    void insertNonFull(bTreeNode* node, int key);

    void splitChild(bTreeNode* parent, int index);
};

// ---------- Implementações ----------

void bTree::insert(int key)
{
    
    
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
        if(node->children[i]->keys.size() == 2 * t -1){
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
    parent->keys.push_back(0);
    int lastIndex = parent->keys.size() -1;
    for(int i = lastIndex; i > index; i--){
        parent->keys[i] = parent->keys[i -1];
    }
    parent->keys[index] = middleKey;
    parent->children.push_back(nullptr);
    for(int i = parent->children.size() -1; i > index +1; i--){
        parent->children[i] = parent->children[i -1];
    }
    parent->children[index +1] = newChild;
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

    std::println("teste");
    
    return 0;
}
