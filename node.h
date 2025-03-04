#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>

class Node {
  private: 
    std::string name;
    Node* parent;
    std::vector<Node *> children;
    double length;
    std::vector<double> strat;
    std::string note;

  public:
    Node();  
    explicit Node(const std::string& name);  
    ~Node(); 

    void update_strat_range(double fad, double lad);
    std::string get_name();
    void update_name(std::string new_name);
    Node* get_parent();
    void add_parent(Node* new_parent);
    void insert_child(Node* new_child);
    std::vector<Node *> get_children();
    std::vector<Node *> get_postorder_vector(); 
    std::vector<Node *> get_preorder_vector(); 
    void add_note(std::string note);
    void setBL(double brlen);
    std::string get_newick_repr(bool bl) const;
};

#endif // NODE_H