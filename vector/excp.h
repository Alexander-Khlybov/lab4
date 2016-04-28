#pragma once

using namespace std;

class myExcp : public exception {
protected:
    const char* excp_;
public:
    myExcp(const char* s) { excp_ = s;}
    virtual const char* what() const throw()
    {
        return excp_;
    }
};
