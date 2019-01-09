#include "darray.h"

size_t Darray::len() const
{
    return len_;
}

Darray::Darray()
{
    arr_ = (double *)malloc(sizeof(double));
    if(!arr_)
        throw std::bad_alloc();
    arr_[0] = 0;
    len_ = 1;
}

Darray::Darray(const Darray &d)
{
    len_ = d.len_;
    arr_ = (double *)malloc(d.len_ * sizeof(double));
    if(!arr_)
        throw std::bad_alloc();
    memcpy(arr_, d.arr_, d.len_ * sizeof(double));
}

Darray::Darray(const double *d, const size_t dlen_)
{
    len_ = dlen_;
    arr_ = (double *)malloc(dlen_ * sizeof(double));
    if(!arr_)
        throw std::bad_alloc();
    memcpy(arr_, d, dlen_ * sizeof(double));
}

Darray::~Darray()
{
    free(arr_);
}

double & Darray::operator[](const size_t k)
{
    if(k >= len_)
    {
        size_t p = len_;
        len_ = k + 1;
        double *arr1_ = (double *)malloc(p * sizeof(double));
        if(!arr1_)
            throw std::bad_alloc();
        memcpy(arr1_, arr_, len_ * sizeof(double));
        free(arr_);
        arr_ = (double *)malloc((k + 1) * sizeof(double));
        if(!arr_)
        {throw std::bad_alloc();}
        for(int j = 0; j < p; j++)
            arr_[j] = arr1_[j];
        for(int u = p; u < k + 1; u++)
            arr_[u] = 0;
        free(arr1_);
    }
    return arr_[k];
}

Darray & Darray::operator= (const Darray &a)
{
    double *arr1_ = (double *)malloc(len_ * sizeof(double));
    if(!arr1_) throw std::bad_alloc();
    for(int j = 0; j < len_; j++)
        arr1_[j] = arr_[j];
    free(arr_);
    arr_ = (double *)malloc(a.len_ * sizeof(double));
    if(!arr_)
        throw std::bad_alloc();
    for(int j = 0; j < a.len_; j++)
        arr_[j] = a.arr_[j];
    len_ = a.len_;
    free(arr1_);
    return *this;
}

Darray & Darray::operator+ (const Darray &a)
{
    Darray *c = new Darray();
    size_t m = len_ > a.len_ ? len_ : a.len_;
    c->len_ = m;
    free(c->arr_);
    c->arr_ = (double *)malloc(m * sizeof(double));
    if(len_ > a.len_)
    {
         for(int i = 0; i < a.len_; i++)
             c->arr_[i] = arr_[i] + a.arr_[i];
         for(int i = a.len_; i < len_; i++)
             c->arr_[i] = arr_[i];
    }
    else
    {
         for(int i = 0; i < len_; i++)
             c->arr_[i] = arr_[i] + a.arr_[i];
         for(int i = len_; i < a.len_; i++)
             c->arr_[i] = a.arr_[i];
    }
    return *c;
}

Darray & Darray::operator& (const double a)
{
    double *arr1_ = (double *)malloc(len_ * sizeof(double));
    if(!arr1_) {throw std::bad_alloc();}
    for(int j = 0; j < len_; j++)
        arr1_[j] = arr_[j];
    free(arr_);
    arr_ = (double *)malloc((len_ + 1) * sizeof(double));
    if(!arr_)
        throw std::bad_alloc();
    for(int j = 0; j < len_; j++)
        arr_[j] = arr1_[j];
    arr_[len_] = a;
    len_ = len_ + 1;
    free(arr1_);
}

void Darray::paste(const size_t i, const double a)
{
    double *arr1_ = (double *)malloc(len_ * sizeof(double));
    if(!arr1_) {throw std::bad_alloc();}
    for(int j = 0; j < len_; j++) arr1_[j] = arr_[j];
    free(arr_);
    if(i >= len_)
    {
        arr_ = (double *)malloc((i + 1) * sizeof(double));
        if(!arr_)
            throw std::bad_alloc();
        for(int j = 0; j < len_; j++)
            arr_[j] = arr1_[j];
        for(int j = len_; j < i; j++)
            arr_[j] = arr1_[j];
        arr_[i] = a;
        len_ = i + 1;
    }
    else
    {
        arr_ = (double *)malloc((len_ + 1) * sizeof(double));
        if(!arr_)
            throw std::bad_alloc();
        for(int j = 0; j < i; j++)
            arr_[j] = arr1_[j];
        arr_[i] = a;
        for(int j = i + 1; j < len_ + 1; j++)
            arr_[j] = arr1_[j - 1];
        len_++;
    }
    free(arr1_);
}

void Darray::del(const size_t i)
{
    if(i < 0) throw 1;
    else
    {
        if(i < len_)
        {
            double *arr1_ = (double *)malloc(len_ * sizeof(double));
            if(!arr1_)
                throw std::bad_alloc();
            for(int j = 0; j < len_; j++) a
                    rr1_[j] = arr_[j];
            free(arr_);
            arr_ = (double *)malloc((len_ - 1) * sizeof(double));
            for(int j = 0; j < i; j++)
                arr_[j] = arr1_[j];
            for(int j = i; j < len_ - 1; j++)
                arr_[j] = arr1_[j + 1];
            len_--;
            free(arr1_);
        }
    }
}

void Darray::remake(const size_t i)
{
    if(i < 1) throw 2;
    else
    {
        double *arr1_ = (double *)malloc(len_ * sizeof(double));
        if(!arr1_)
            throw std::bad_alloc();
        for(int j = 0; j < len_; j++)
            arr1_[j] = arr_[j];
        free(arr_);
        arr_ = (double *)malloc(i * sizeof(double));
        if(!arr_) {throw std::bad_alloc();}
        if(i >= len_)
        {
            for(int j = 0; j < len_; j++)
                arr_[j] = arr1_[j];
            for(int j = len_; j < i; j++)
                arr_[j] = 0;
        }
        else
        {
            for(int j = 0; j < i; j++)
                arr_[j] = arr1_[j];
        }
        len_ = i;
    }
}

Darray* Darray::ret() const
{
    Darray *a = new Darray();
    return a;
}

int main()
{
    return 0;
}
