#include "node.h"
#include "tree.h"


using namespace std;

int main() {
    Node my_node("sp2");
    Node par_node;

    par_node.update_name("sp1");
    par_node.insert_child(&my_node);
    my_node.get_parent()->update_strat_range(59.4, 56.7);
    
    Node desc2("sp3"), desc3("sp4");
    par_node.insert_child(&desc2);
    desc2.insert_child(&desc3);

    Tree tree(&par_node);

    cout << tree.get_root()->get_name();

    //vector<Node *> po_nodes; 
    //po_nodes = par_node.get_postorder_vector();

    cout << "\n\nPOSTORDER:\n";
    
    for (Node* n : tree.get_postorder_vector(false)) {
        if (n->get_parent() != nullptr) {
            cout << "\n" << n->get_name() << " " << n->get_parent()->get_name() << "\n";
        } else {
            cout << "\n" << n->get_name() << "\n";
        }
    }

    cout << "\n\nPREORDER:\n";
    //vector<Node *> pr_nodes = par_node.get_preorder_vector();
    
    for (Node* n : tree.get_preorder_vector(false)) {
        if (n->get_parent() != nullptr) {
            cout << "\n" << n->get_name() << " " << n->get_parent()->get_name() << "\n";
        } else {
            cout << "\n" << n->get_name() << "\n";
        }
    }
    

    cout << "\n" << tree.get_newick(false) << "\n";

    return 0;
}
