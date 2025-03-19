//#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>

#include "node.h"
#include "tree.h"
#include "tree_reader.h"

Tree parse_newick(const std::string& instr) {
    Tree tree;
    Node* root = nullptr;
    Node* curnode = nullptr;
    bool start = true;
    size_t index = 0;
    char nextchar = instr[index];
    bool keepgoing = true;

    while (keepgoing) {
        if (nextchar == '(') {  
            if (start) {  
                root = new Node();
                tree.update_root(root);
                curnode = root;
                start = false;
            } else {  
                Node* newnode = new Node();
                curnode->insert_child(newnode);
                curnode = newnode;
            }
        } else if (nextchar == '[') {  
            std::string note;
            index++;
            nextchar = instr[index];

            while (nextchar != ']') {
                note += nextchar;
                index++;
                nextchar = instr[index];
            }
            curnode->add_note(note);
        } else if (nextchar == ',') {  
            curnode = curnode->get_parent();
        } else if (nextchar == ')') {  
            curnode = curnode->get_parent();
            index++;
            nextchar = instr[index];
            std::string name;

            while (nextchar != ',' && nextchar != ')' && nextchar != ':' &&
                   nextchar != ';' && nextchar != '[') {
                name += nextchar;
                if (index < instr.length() - 1) {
                    index++;
                    nextchar = instr[index];
                } else {
                    keepgoing = false;
                    break;
                }
            }
            curnode->update_name(name);
            index--;
        } else if (nextchar == ';') {  
            keepgoing = false;
            break;
        } else if (nextchar == ':') {  
            index++;
            nextchar = instr[index];
            std::string brlen;

            while (nextchar != ',' && nextchar != ')' && nextchar != ':' &&
                   nextchar != ';' && nextchar != '[') {
                brlen += nextchar;
                index++;
                nextchar = instr[index];
            }
            curnode->set_length(std::stod(brlen));
            index--;
        } else if (nextchar == ' ') {  
            index++;
            nextchar = instr[index];
        } else {  
            Node* newnode = new Node();
            curnode->insert_child(newnode);
            curnode = newnode;
            std::string name;

            while (nextchar != ',' && nextchar != ')' && nextchar != ':' &&
                   nextchar != ';' && nextchar != '[') {
                name += nextchar;
                index++;
                nextchar = instr[index];
            }
            curnode->update_name(name);
            index--;
        }
        if (index < instr.length() - 1) {
            index++;
        }
        nextchar = instr[index];
    }

    tree.compute_postorder_vector();
    tree.compute_preorder_vector();
    return tree;
}
