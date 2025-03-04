#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

#include "node.h"
#include "tree.h"
#include "tree_reader.h"
//#include "utils.h"


TreeReader::TreeReader() = default;

Tree TreeReader::read_newick (const std::string& pb) {
    //auto * tree = new Tree();
    //std::string pb = trees;
    Tree tree;
    unsigned int x = 0;
    char nextChar = pb.at(x);
    bool start = true;
    bool keepGoing = true;
    bool in_quote = false;
    bool hasAnnotations = false;
    bool hasInternalNodeNames = false;
    char quoteType = '\0';
    Node * currNode = nullptr;
    double sumEL = 0.0;
    while (keepGoing) {
        if (nextChar == '(') {
            if (start) {
                //auto * root = new Node();
                Node root;
                //Tree tree(&root);
                tree.update_root(&root);
                //tree->setRoot(root);
                currNode = &root;
                start = false;
            } else {
                if (currNode == nullptr) {
                    std::cerr << "Malformed newick string. Can read until char " << x << "." << std::endl;
                    exit(1);
                }
                //auto * newNode = new Node(currNode);
                Node new_node; 
                //currNode->addChild(*newNode);
                currNode->insert_child(&new_node);
                currNode = &new_node;
            }
        } else if (nextChar == ',') {
            currNode = currNode->get_parent();
        } else if (nextChar == ')') {
            // internal named node (or more likely support annotation)
            currNode = currNode->get_parent();
            x++;
            nextChar = pb.at(x);
            
            std::string node_name;
            bool goingName = true;
            in_quote = false;
            if (nextChar == ',' || nextChar == ')' || nextChar == ':'
                || nextChar == ';' || nextChar == '[') {
                goingName = false;
            } else if (nextChar == '"' || nextChar == '\'') {
                in_quote = true;
                quoteType = nextChar;
                node_name += nextChar;
            }
            if (!in_quote) {
                while (goingName) {
                    node_name += nextChar;
                    x++;
                    nextChar = pb.at(x);
                    if (nextChar == ',' || nextChar == ')' || nextChar == ':'
                        || nextChar == '[' || nextChar == ';') {
                        break;
                    }
                }
                x--;
            } else {
                x++;
                nextChar = pb.at(x);
                while (goingName) {
                    node_name += nextChar;
                    x++;
                    nextChar = pb.at(x);
                    if (nextChar == quoteType) {
                        node_name += nextChar;
                        if (quoteType == '"') {
                            break;
                        }
                        // check for double single quotes
                        x++;
                        nextChar = pb.at(x);
                        if (nextChar != quoteType) {
                            x--;
                            break;
                        }
                    }
                } 
            } // work on edge
            currNode->update_name(node_name);
            
            if (!node_name.empty()) {
                hasInternalNodeNames = true;
            }
            if (!in_quote) {
                //x--;
            }
        } else if (nextChar == ';') {
            keepGoing = false;
        } else if (nextChar == ':') {
            // edge length
            x++;
            nextChar = pb.at(x);
            std::string edgeL;
            while (true) {
                edgeL += nextChar;
                x++;
                nextChar = pb.at(x);
                if (nextChar == ',' || nextChar == ')' || nextChar == ':'
                    || nextChar == ';'|| nextChar == '[') {
                    break;
                }
            } // work on edge
            double edd = strtod(edgeL.c_str(), nullptr);
            currNode->setBL(edd);
            sumEL += edd;
            x--;
        }
        
        else if (nextChar == '[') {
            hasAnnotations = true;
            x++;
            nextChar = pb.at(x);
            std::string note;
            while (true) {
                note += nextChar;
                x++;
                nextChar = pb.at(x);
                if (nextChar == ']' ) {
                    break;
                }
            }
            currNode->add_note(note);
        } else if (nextChar == ' ') {
            // skip whitespace
        }
        // external named node
        else {
            //auto * newNode = new Node(currNode);
            Node new_node;
            currNode->insert_child(&new_node);
            currNode = &new_node;
            std::string node_name;
            bool goingName = true;
            in_quote = false;
            if (nextChar == '"' || nextChar == '\'') {
                in_quote = true;
                quoteType = nextChar;
                node_name += nextChar;
            }
            if (!in_quote) {
                while (goingName) {
                    node_name += nextChar;
                    x++;
                    nextChar = pb.at(x);
                    if (nextChar == ',' || nextChar == ')' || nextChar == ':'
                        || nextChar == '[') {
                        break;
                    }
                }
                x--;
            } else {
                x++;
                nextChar = pb.at(x);
                while (goingName) {
                    node_name += nextChar;
                    x++;
                    nextChar = pb.at(x);
                    if (nextChar == quoteType) {
                        node_name += nextChar;
                        if (quoteType == '"') {
                            break;
                        }
                        
                        x++;
                        nextChar = pb.at(x);
                        if (nextChar != quoteType) {
                            x--;
                            break;
                        }
                    }
                } 
            }
            
            new_node.update_name(node_name);
        }
        if (x < pb.length() - 1) {
            x++;
        }
        nextChar = pb.at(x);
    }
    bool hasEdgeLengths = sumEL > 0.0;
    tree.compute_postorder_vector();
    tree.compute_preorder_vector();
    return tree;
}
