/*
Author: Elijah Cano
Course: CSCI 335
Assignment: Homework 2
*/

#ifndef SEQUENCEMAP_HPP
#define SEQUENCEMAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SequenceMap{
    public:
        //All of the big five are set to default.
        SequenceMap(const SequenceMap &a)=default;
        SequenceMap& operator=(const SequenceMap &a)=default;
        SequenceMap(SequenceMap &&a)=default;
        SequenceMap& operator=(SequenceMap &&a)=default;
        ~SequenceMap()=default;

        /*
        The following is a parametized constructor that gives values to 
        memebers recognition_sequence_ and enzyme_acronyms_.
        */
        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }

        //returns true if recognition_sequence_'s string value is alphabetically lower than rhs's recognition_sequence_.
        bool operator<(const SequenceMap &rhs) const{
            return this->recognition_sequence_ < rhs.recognition_sequence_;
        }

        //Merges other_sequence's enzyme_acronyms_ into this' enzyme_acronyms_.
        void Merge(const SequenceMap &other_sequence){
            for(unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
                this->enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
            }
        }

    //Outputs all of the elements in enzyme_acronyms.
    friend ostream& operator<<(ostream &out, const SequenceMap &a){
        for(unsigned int i = 0; i < a.enzyme_acronyms_.size(); i++){
            if(i == a.enzyme_acronyms_[i].size()-1){
                out << a.enzyme_acronyms_[i] << " ";
            }
            out << a.enzyme_acronyms_[i] << " ";
        }
        return out;
    }

    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};
#endif 