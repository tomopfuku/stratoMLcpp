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
    double height;
    std::vector<double> strat;
    std::string note;
    bool obs_taxon;

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
    void set_length(double brlen);
    double get_height();
    std::string get_newick_repr(bool bl) const;
    bool is_obs_taxon();
};

#endif // NODE_H