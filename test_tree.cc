/*
Author: Elijah Cano
Course: CSCI 335
Assignment: Homework 2
*/

#include "avl_tree.h"
#include "SequenceMap.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace {

/*
Reads through the database file db_filename, parses
all the data, then creates sequence map objects with that
data, and then inserts those objects into the tree. After 
insertion, test tree makes specific calls to avl tree methods such 
as getting the number of nodes within the tree, average depth, as well as
other methods that keep track of the number of recursive calls that
are made in respect to themselves.
*/
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree){
  string fileJunk;
  int x = 0;
  string enzStr = "";
  string recogStr = "";
  string newDb_line = "";
  string db_line;
  ifstream inFile;
  ifstream inFile2;
  inFile.open(db_filename);

  //The following will skip the first ten lines within db_filename.
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

  inFile2.open(seq_filename);
  float counter = 0.0;
  float query = 0.0;
  string sInInputFile = "";

  while(getline(inFile2, sInInputFile, '\n')){
    SequenceMap newMap(sInInputFile, "");
    a_tree.findPublicFunctionForRecurrences(newMap, counter, query);
  }

  cout << query << endl;
  float averageFindRecurrences = counter / query;
  cout << averageFindRecurrences << endl;

  inFile2.close();
  inFile2.open(seq_filename);

  float rc = 0.0;
  float successfulRemoves = 0.0;
  int lineInFile = 0;
  int remCounter = 0;
  string sInInputFile2 = "";

  while(getline(inFile2, sInInputFile2, '\n')){
    if(lineInFile % 2 == 0){
      SequenceMap newMap(sInInputFile2, "");
      a_tree.remove(newMap, rc, successfulRemoves);
      remCounter++;
    }
    lineInFile++;
  }

  float averageRemoveRecurrences = rc / remCounter;
  cout << successfulRemoves << endl;
  cout << averageRemoveRecurrences << endl;
  cout  << a_tree.countNumberNodesPublic() << endl;
  cout << a_tree.averageDepthPublic() << endl;
  cout << a_tree.averageDepthPublic()/log2(a_tree.countNumberNodesPublic()) << endl;
}

}  // namespace

int main(int argc, char **argv){
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;

  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
