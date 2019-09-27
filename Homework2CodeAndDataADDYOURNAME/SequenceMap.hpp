#ifndef SEQUENCEMAP_HPP
#define SEQUENCEMAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SequenceMap{
    public:
        SequenceMap(const SequenceMap &a)=default;
        SequenceMap& operator=(const SequenceMap &a)=default;
        SequenceMap(SequenceMap &&a)=default;
        SequenceMap& operator=(SequenceMap &&a)=default;
        ~SequenceMap()=default;

        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }

        bool operator<(const SequenceMap &rhs) const{
            return this->recognition_sequence_ < rhs.recognition_sequence_;
        }


        void Merge(const SequenceMap &other_sequence){
            for(int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
                this->enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
            }
        }

    friend ostream& operator<<(ostream &out, const SequenceMap &a){
    for(int i = 0; i < a.enzyme_acronyms_.size(); i++){
        if(i == a.enzyme_acronyms_[i].size()-1){
            out << a.enzyme_acronyms_[i] << " ";
        }
        out << a.enzyme_acronyms_[i] << " ";
    }
    //out << "\n";
    return out;
}

    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};



#endif 