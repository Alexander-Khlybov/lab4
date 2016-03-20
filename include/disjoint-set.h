#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

#include "tvector.h"

using namespace std;

class DISJOINT_SET{
    TVector     U_;
    size_t      count_;
public:
    DISJOINT_SET    (int universalSetSize = 1) : U_(universalSetSize), count_(0) {
                        for (int i = 0; i < U_.GetSize(); i++) U_[i] = -1;}
    DISJOINT_SET    (const DISJOINT_SET& set) : U_(set.U_), count_(set.count_) {}
    ~DISJOINT_SET   (void) {}

    int     createSet           (int);
    void    removeSet           (int);
    void    removeNodeFromSet   (int, int);
    int     uniteSets           (int, int);
    int     findSet             (int)const;
    int     getNumberOfSets     (void)const { return count_; }

    TVector getUniversalSet (void)const { return U_; }
    TVector getSet          (int)const;

    friend ostream& operator<< (ostream& out, const DISJOINT_SET& set) {

        for (int j = 0; j < set.getUniversalSet().GetSize(); j++) {
            if (set.getUniversalSet()[j] == j) cout << "{" << set.getSet(j) << "}\n";
        }
        return out;
    }
};

#endif