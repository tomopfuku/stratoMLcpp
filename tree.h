#ifndef SML_TREE_H
#define SML_TREE_H

#include "node.h"
#include <vector>

class Tree {
    private: 
        Node* root;
        std::vector<Node *> preorder_nodes, postorder_nodes;
    
    public:
        Tree();  
        explicit Tree(Node * root);  
        ~Tree(); 

        Node * get_root();
        void compute_preorder_vector();
        void compute_postorder_vector();
        std::vector<Node *> get_preorder_vector(bool compute);
        std::vector<Node *> get_postorder_vector(bool compute);
        void update_root(Node * new_root);
        std::string get_newick(bool bl) const;
};

#endif // SML_TREE_H 
