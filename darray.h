#ifdef _DARRAY_H_
#define _DARRAY_H_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

class Darray
{
    double *arr_;
    size_t len_;
public:
    Darray();
    Darray(const Darray &d);
    Darray(const double *d, const size_t dlen_);
    ~Darray();
    double & operator[] (const size_t i);
    Darray & operator= (const Darray &a);
    Darray & operator+ (const Darray &a);
    Darray & operator& (const double a);
    size_t len() const;
    void paste(const size_t i, const double a);
    void del(const size_t i);
    Darray* ret() const;
    void remake(const size_t i);
};
#endif
