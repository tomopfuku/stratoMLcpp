#include "node.h"
#include "tree.h"

using namespace std;

Tree::Tree() : root(nullptr) {}

Tree::Tree(Node* root) : root(root) {
    compute_preorder_vector();
    compute_postorder_vector();
}

Tree::~Tree() {}


Node * Tree::get_root() {
    return root;
}

void Tree::compute_preorder_vector() {
    preorder_nodes = root->get_preorder_vector();
}

void Tree::compute_postorder_vector() {
    postorder_nodes = root->get_postorder_vector();
}

std::vector<Node *> Tree::get_preorder_vector(bool compute) {
    if (compute) {
        compute_preorder_vector();
    }
    return preorder_nodes;
}

std::vector<Node *> Tree::get_postorder_vector(bool compute) {
    if (compute) {
        compute_postorder_vector();
    }
    return postorder_nodes;
}

void Tree::update_root(Node * new_root) {
    root = new_root;
}

string Tree::get_newick(bool bl) const {
    string nwk = root->get_newick_repr(bl);
    return nwk + ";";
}
