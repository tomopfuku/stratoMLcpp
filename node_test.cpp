#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
  private: 
    string name;
    Node* parent;
    vector<Node *> children;
    double length;
    vector<double> strat;

  public:
  void update_strat_range(double fad, double lad)
  {
    strat.push_back(fad);
    strat.push_back(lad);
  }

  string get_name()
  {
    return name;
  }

  void update_name(string new_name)
  {
    name = new_name;
  }

  Node* get_parent()
  {
    return parent;
  }

  void add_parent(Node* new_parent)
  {
    parent = new_parent;
    parent->children.push_back(this);
  }

  void add_child(Node* new_child) 
  {
    children.push_back(new_child);
    new_child->parent = this;
  }

  vector<Node *> get_children()
  {
    return children; 
  }

};

int main() {
  Node my_node;
  Node par_node;

  par_node.update_name("sp1");
  my_node.update_name("sp2");
  my_node.add_parent(&par_node);
  //par_Node.children[0] = &my_Node;
  //par_node.children.push_back(&my_node);
  my_node.get_parent()->add_child(&my_node);
  my_node.get_parent()->update_strat_range(59.4,56.7);

  cout << my_node.get_name() << " " << my_node.get_parent()->get_name() << " " << par_node.get_children().size() << "\n";
  return 0;
}