// <Your name>
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "SequenceMap.hpp"
// You will have to add #include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree){
  
  string fileJunk;
  int x = 0;
  string enzStr = "";
  string recogStr = "";
  string newDb_line = "";
  string db_line;
  ifstream inFile;
  inFile.open(db_filename);

  while(x < 10){
    getline(inFile, fileJunk, '\n');
    x++;
  }

  while(getline(inFile, db_line, '\n')){
    newDb_line = db_line.substr(0, db_line.length()-2);

    stringstream ss(newDb_line);
    getline(ss, enzStr, '/');
    while(getline(ss, recogStr, '/')){
      SequenceMap newSequenceMap(recogStr, enzStr);
      a_tree.insert(newSequenceMap);
    }
  }

  cout << "These are the found objects: \n";

  string sInInputFile = "";
  while(getline(cin, sInInputFile)){
    SequenceMap newMap(sInInputFile, "");
    cout << a_tree.findPublicFunction(newMap) << endl;
  }
  
}


} //namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  //a_tree.printTree();
  
  
  
  return 0;
}
