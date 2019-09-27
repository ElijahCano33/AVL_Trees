// <Your name>
// Main file for Part2(c) of Homework 2.

#include "avl_tree_modified.h"
// You will have to add #include "sequence_map.h"

#include <iostream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  while(getline(cin, db_line, '/')){
    string an_enz_acro = db_line;
    string a_reco_seq = db_line;
    SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
    a_tree.insert(new_sequence_map);
  } 
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
  AvlTree<int> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
