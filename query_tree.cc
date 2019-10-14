/*
Author: Elijah Cano
Course: CSCI 335
Assignment: Homework 2
*/

#include "avl_tree.h"
#include "SequenceMap.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

namespace {

/*
Reads through the database file db_filename, parses
all the data, then creates sequence map objects with that
data, and then inserts those objects into the tree. After insertion,
new sequence map objects are created from input_part2a.txt and
searched for within the already existing tree.
*/
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

  string sInInputFile = "";
  while(getline(cin, sInInputFile)){
    SequenceMap newMap(sInInputFile, "");
    cout << a_tree.findPublicFunction(newMap) << endl;
  }
  
}

} //namespace

int main(int argc, char **argv){
  if (argc != 2){
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }

  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  
  return 0;
}
