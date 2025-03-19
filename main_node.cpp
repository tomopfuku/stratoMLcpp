#include <iostream>
#include <fstream>
#include <string>
//#include <getopt.h>

#include "tree_reader.h"
#include "utils.h"
#include "node.h"

using namespace std;

int main() {
    vector<string> lines;
    lines = readlines("test/test.tre");
    cout << "\n" << lines.size() << "\n";
    //cout << lines[0];
    string nwk = lines[0];
    Tree tree;
    cout << nwk << std::endl << "\n";
    tree = parse_newick(nwk);
    cout << &tree << "\n";

    /*
    unsigned int count = 0;
    for (Node* n : tree.get_postorder_vector(false)) {
        if (n->get_parent() != nullptr ){
            cout << count << " " << n->get_name() << " " << n->get_parent()->get_name() << " HERE\n";
        } else {
            cout << count << " " << n->get_name() << " " << " ROOT\n";
        }
        count++;
    }
    */

    cout << tree.get_postorder_vector(false).size() << " PO_VEC_SIZE\n";
    cout << tree.get_newick(false) << std::endl ; 

    read_strat_ranges("test/test.strat",tree);
    return 0;
}
