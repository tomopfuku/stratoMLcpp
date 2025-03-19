#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
//#include <getopt.h>

//#include "node.h"
#include "tree.h"

using namespace std;

// just a simple utility to read in a file and output a vector where each element is a line 
vector<string> readlines(string flnm) {
    vector<string> file_lines;
    fstream fl;
    fl.open(flnm, ios::in); 
    if (fl.is_open()) {
        string line;
        while (getline(fl,line)) {
            //cout << line;
            file_lines.push_back(line);
        }
    }
    return file_lines;
}

vector<string> split_str(string instr, char delim) {
    vector<string> spls;
    string cur_tok = "";
    for (char i : instr) {
        if (i == delim) {
            spls.push_back(cur_tok);
            //cout << cur_tok << std::endl;
            cur_tok = "";
        } else {
        cur_tok += i;
        }
    }
    spls.push_back(cur_tok);
    //for (string substr : spls) {
    //    cout << substr << endl;
    //}
    return spls;
}

void read_strat_ranges(string flnm, Tree tree) {
    vector<string> file_lines = readlines(flnm);
    string header = file_lines[0];
    map<string, vector<double>> ranges;
    for (int i = 1; i < file_lines.size(); i++) {
        string curline = file_lines[i];
        vector<string> spls = split_str(curline, ' ');
        //cout << curline << std::endl;
        string sp = spls[0];
        // TODO: ADD PROPER TYPE CHECK FOR fad AND lad
        double fad = stod(spls[1]);
        double lad = stod(spls[2]);
        vector<double> strat = {fad,lad};
        ranges[sp] = strat;
    }

    vector<Node *> nodes = tree.get_postorder_vector(false);
    for (Node* n : nodes) {
        if (n->get_name() != "") {
            try {
                if (ranges.find(n->get_name()) != ranges.end()) {
                vector<double> strat = ranges[n->get_name()];
                n->update_strat_range(strat[0],strat[1]);
                cout << n->get_name() << " " << strat[0] << " " << strat[1] << endl;
                } else {
                    throw n->get_name();
                }
            } 
            catch (string missing_name) {
                cout << "ERROR: taxon " << missing_name << " is in the tree but missing a stratigraphic range\n";
                std::exit(0);
            }
        }
    }
}


