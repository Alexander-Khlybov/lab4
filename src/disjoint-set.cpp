#include "disjoint-set.h"

void DISJOINT_SET::createSet(int root){
    if ((root < 0) || (root >= U_.GetSize()))
        throw myExcp("Out of range.");
    if (U_[root] != -1)
        throw myExcp("This element is already in use.");
    U_[root] = root;
    ++count_;
}

void DISJOINT_SET::uniteSets(int firstRoot, int secondRoot){
    if (firstRoot == secondRoot) return;

    if ((firstRoot < 0) || (firstRoot >= U_.GetSize())||
        (secondRoot < 0) || (secondRoot >= U_.GetSize()))
        throw myExcp("Out of range.");
    if ((U_[firstRoot] == -1) || (U_[secondRoot] == -1))
        throw myExcp("One of sets is empty.");
    if ((U_[firstRoot] != firstRoot) || (U_[secondRoot] != secondRoot))
        throw myExcp("One of arguments is not root.");

    if (firstRoot < secondRoot) U_[secondRoot] = firstRoot;
    else U_[firstRoot] = secondRoot;
    --count_;
}

int DISJOINT_SET::findSet(int key){
    if ((key < 0) || (key >= U_.GetSize()))
        throw myExcp("Out of range.");
    if (U_[key] == -1) return -1;

    while (U_[key] != key)
        key = U_[key];
    return key;
}

TVector DISJOINT_SET::getSet(int root) const{
    if ((root < 0) || (root >= U_.GetSize()))
        throw myExcp("Out of range.");
    TVector tmp = U_;
    if (tmp[root] != root)
        throw myExcp("Argument is not root.");
    stack<int> st1;
    PRIORITY_QUEUE q(U_.GetSize() - count_ + 1);
    st1.push(root);
    while (!st1.empty()) {
        root = st1.top();
        st1.pop();
        tmp[root] = -1;
        q.push(root);
        for (int i = 0; i < U_.GetSize(); i++) {
            if (tmp[i] == root)
                st1.push(i);
        }
    }
    

    TVector res(q.getSize());
    int i = 0;
    while (q.getSize() != 0) {
        res[i++] = q.back();
        q.pop();
    }
    return res;
}
