#ifndef __TVECTOR_H__
#define __TVECTOR_H__

#ifndef _IOSTREAM_
#include <iostream>
#endif

#include "excp.h"

using namespace std;

typedef int KeyType;

class TVector {
private:
  KeyType *pVector_;
  int size_;
public:

  TVector (int s = 0);
  TVector (const TVector &v);
  ~TVector(void);

  int GetSize(void){ return size_; }

  KeyType&  operator[](int pos);
  int       operator==(const TVector &v) const;
  int       operator!=(const TVector &v) const;
  TVector&  operator= (const TVector &v);

  friend istream& operator>>(istream &in, TVector &v){
    for (int i = 0; i < v.size_; i++)
      in >> v.pVector_[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v){
    for (int i = 0; i < v.size_; i++)
      out << v.pVector_[i] << "\t";
    return out;
  }
};

#endif