#ifndef SML_TREE_READER_H
#define SML_TREE_READER_H

#include <string>
#include <map>
#include <iostream>

#include "tree.h"


class TreeReader {
public:
    TreeReader ();
    Tree read_newick (const std::string& pb);
};


#endif /* SML_TREE_READER_H */