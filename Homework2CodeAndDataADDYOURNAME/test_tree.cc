// <Your name>
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include <cmath>
#include "SequenceMap.hpp"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
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

  cout  << a_tree.countNumberNodesPublic() << endl;

  cout << a_tree.averageDepthPublic() << endl;

  cout << a_tree.averageDepthPublic()/log2(a_tree.countNumberNodesPublic()) << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);
  //a_tree.countNumberNodesPublic();

  return 0;
}
