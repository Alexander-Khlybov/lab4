#pragma once

#include "priority_queue.hpp"
#include <stack>

template <class KeyType>
class DISJOINT_SET{
    vector<KeyType>    U_;
    size_t              count_;
public:
    DISJOINT_SET<KeyType>(int universalSetSize = 1) : U_(universalSetSize), count_(0) {
                        for (int i = 0; i < U_.size(); i++) U_[i] = -1;}
    DISJOINT_SET<KeyType>(const DISJOINT_SET<KeyType>& set) : U_(set.U_), count_(set.count_) {}
    ~DISJOINT_SET<KeyType>(void) {}

    void    createSet           (int);
    void    uniteSets           (int, int);
    int     findSet             (int);
    int     getNumberOfSets     (void)const { return count_; }

    vector<KeyType> getUniversalSet (void)const { return U_; }
    vector<KeyType> getSet          (int)const;

    friend std::ostream& operator<< (std::ostream& out, const DISJOINT_SET<KeyType>& set) {
        for (int j = 0; j < set.getUniversalSet().GetSize(); j++) {
            if (set.getUniversalSet()[j] == j) out << "{" << set.getSet(j) << "}\n";
        }
        return out;
    }
};

template <class KeyType>
void DISJOINT_SET<KeyType>::createSet(int root) {
    if ((root < 0) || (root >= U_.size()))
        throw myExcp("Out of range.");
    if (U_[root] != -1)
        throw myExcp("This element is already in use.");
    U_[root] = root;
    ++count_;
}

template <class KeyType>
void DISJOINT_SET<KeyType>::uniteSets(int firstRoot, int secondRoot) {
    if (firstRoot == secondRoot) return;
    if ((firstRoot < 0) || (firstRoot >= U_.size()) ||
        (secondRoot < 0) || (secondRoot >= U_.size()))
        throw myExcp("Out of range.");
    if ((U_[firstRoot] == -1) || (U_[secondRoot] == -1))
        throw myExcp("One of sets is empty.");
    if ((U_[firstRoot] != firstRoot) || (U_[secondRoot] != secondRoot))
        throw myExcp("One of arguments is not root.");
    if (firstRoot < secondRoot) U_[secondRoot] = firstRoot;
    else U_[firstRoot] = secondRoot;
    --count_;
}

template <class KeyType>
int DISJOINT_SET<KeyType>::findSet(int key) {
    if ((key < 0) || (key >= U_.size()))
        throw myExcp("Out of range.");
    if (U_[key] == -1) return -1;
    while (U_[key] != key)
        key = U_[key];
    return key;
}

template <class KeyType>
vector<KeyType> DISJOINT_SET<KeyType>::getSet(int root) const {
    if ((root < 0) || (root >= U_.size()))
        throw myExcp("Out of range.");
    vector<KeyType> tmp = U_;
    if (tmp[root] != root)
        throw myExcp("Argument is not root.");
    stack<int> st1;
    PRIORITY_QUEUE_ON_D_HEAP<KeyType> q(U_.size() - count_ + 1);
    st1.push(root);
    while (!st1.empty()) {
        root = st1.top();
        st1.pop();
        tmp[root] = -1;
        q.push(root);
        for (int i = 0; i < U_.size(); i++) {
            if (tmp[i] == root)
                st1.push(i);
        }
    }
    vector<KeyType> res(q.getSize());
    int i = 0;
    while (q.getSize() != 0) {
        res[i++] = q.back();
        q.pop();
    }
    return res;
}
