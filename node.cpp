#include "node.h"
#include <stack>
#include <unordered_map>

using namespace std;

Node::Node() : name(""), parent(nullptr), length(0.0), note ("") {}

Node::Node(const string& name) : name(name), parent(nullptr), length(0.0), note("") {}

Node::~Node() {}

void Node::update_strat_range(double fad, double lad) {
    strat.push_back(fad);
    strat.push_back(lad);
}

string Node::get_name() {
    return name;
}

void Node::update_name(string new_name) {
    name = new_name;
}

Node* Node::get_parent() {
    return parent;
}

void Node::add_parent(Node* new_parent) {
    parent = new_parent;
}

void Node::insert_child(Node* new_child) {
    children.push_back(new_child);
    new_child->add_parent(this);
}

vector<Node *> Node::get_children() {
    return children;
}

void add_note(string note) {
    note = note;
}

vector<Node *> Node::get_postorder_vector() {
    vector<Node*> postorder_nodes;
    stack<Node*> node_stack;
    unordered_map<Node*, bool> visited;

    node_stack.push(this);
    while (!node_stack.empty()) {
        Node* current = node_stack.top();
        bool all_children_visited = true;
        for (Node* chd : current->children) {
            if (!visited[chd]) {
                node_stack.push(chd);
                all_children_visited = false;
            }
        }

        if (all_children_visited) {
            node_stack.pop();
            postorder_nodes.push_back(current);
            visited[current] = true;
        }
    }

    return postorder_nodes;
}


vector<Node *> Node::get_preorder_vector() {
    vector<Node*> preorder_nodes;
    stack<Node*> node_stack;

    node_stack.push(this);
    while (!node_stack.empty()) {
        Node* current = node_stack.top();
        node_stack.pop();
        preorder_nodes.push_back(current);

        for (Node* chd : current->children) {
            node_stack.push(chd);
        }
    }
    return preorder_nodes;
}

void Node::setBL(double brlen) {
    length = brlen;
}
