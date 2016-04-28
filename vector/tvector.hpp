#pragma once

#include <iostream>
#include "excp.h"

template <class ValType>
class TVector {
private:
  ValType *pVector_;
  int size_;
public:

  TVector (int s = 0);
  TVector (const TVector<ValType>&);
  ~TVector(void);

  int GetSize(void)const{ return size_; }

  ValType&  operator[](int pos);
  int       operator==(const TVector<ValType>&) const;
  int       operator!=(const TVector<ValType>&) const;
  TVector<ValType>&  operator= (const TVector<ValType>&);

  friend std::istream& operator>>(std::istream &in, TVector<ValType>& v){
    for (int i = 0; i < v.size_; i++)
      in >> v.pVector_[i];
    return in;
  }
  friend std::ostream& operator<<(std::ostream &out, const TVector<ValType>& v){
    for (int i = 0; i < v.size_ - 1; i++)
      out << v.pVector_[i] << ",\t";
    if (v.size_ != 0) out << v.pVector_[v.size_ - 1];
    return out;
  }
};


template<class ValType>
TVector<ValType>::TVector(int s) {
    if (s < 0)
        throw myExcp("Length of vector must be positive");

    size_ = s;

    pVector_ = new ValType[size_];

    if (pVector_ == NULL)
        throw myExcp("Bad memory allocation.");
}

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v) {
    size_ = v.size_;
    pVector_ = new ValType[size_];
    if (pVector_ == NULL)
        throw myExcp("Bad memory allocation.");

    for (int i = 0; i < size_; i++)
        pVector_[i] = v.pVector_[i];
}

template<class ValType>
TVector<ValType>::~TVector(void) {

    delete[]pVector_;
}

template<class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if ((pos < 0) || (pos >= size_))
        throw myExcp("Out of range");

    return pVector_[pos];
}

template<class ValType>
int TVector<ValType>::operator== (const TVector &v) const {
    if (this == &v)
        return 1;

    if (size_ != v.size_)
        return 0;

    for (int i = 0; i < size_; i++)
        if (pVector_[i] != v.pVector_[i])
            return 0;

    return 1;
}

template<class ValType>
int TVector<ValType>::operator!=(const TVector &v) const {

    return !(*this == v);
}

template<class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
    if (this != &v)
    {
        size_ = v.size_;
        delete[]pVector_;
        pVector_ = new ValType[size_];
        if (pVector_ == NULL)
            throw myExcp("Bad memory allocation.");

        for (int i = 0; i < size_; i++)
            pVector_[i] = v.pVector_[i];
    }
    return *this;
}
