#include "tvector.h"

TVector::TVector(int s){
    if (s < 0)
      throw myExcp("Length of vector must be positive");

    size_ = s;

    pVector_ = new KeyType[size_];

    if (pVector_ == NULL)
      throw myExcp("Bad memory allocation.");
}

TVector::TVector(const TVector &v){
    size_ = v.size_;
    pVector_ = new KeyType[size_];
    if (pVector_ == NULL)
      throw myExcp("Bad memory allocation.");

    for (int i = 0; i < size_; i++)
        pVector_[i] = v.pVector_[i];
}

TVector::~TVector(void){

    delete[]pVector_;
}

KeyType& TVector::operator[](int pos){
    if ((pos < 0) || (pos >= size_))
      throw myExcp("Out of range");

    return pVector_[pos];
}

int TVector::operator== (const TVector &v) const{
    if (this == &v)
        return 1;

    if (size_ != v.size_)
        return 0;

    for (int i = 0; i < size_; i++)
        if (pVector_[i] != v.pVector_[i])
            return 0;

    return 1;
}

int TVector::operator!=(const TVector &v) const{

    return !(*this == v);
}

TVector& TVector::operator=(const TVector &v){
    if (this != &v)
    {
        size_ = v.size_;
        delete[]pVector_;
        pVector_ = new KeyType[size_];
        if (pVector_ == NULL)
            throw myExcp("Bad memory allocation.");

        for (int i = 0; i < size_; i++)
            pVector_[i] = v.pVector_[i];
    }
    return *this;
}
