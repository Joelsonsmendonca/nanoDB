#include <iostream>
#include <vector>



struct bTreeNode
{
    std::vector<int> keys;
    std::vector<bTreeNode*> children;
    bool isLeaf;
    int t;  

public:
    bTreeNode(int t, bool isLeaf) // constructor
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
    void traverse();

public:
    bTree(int t)
    {
        this->t = t;
        root = new bTreeNode(t, true); // root is initially a leaf node
    }

    void insert(int key)
    {
        // Insertion logic to be implemented
    }
    void traverse()
    {
     
    }

private:
    void traverseNode(bTreeNode* node)
    {

    }

    bTreeNode* searchNode(bTreeNode* node, int key);
};

void bTree::insert(int key)
{

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


int main ()
{

    return 0;
}

    