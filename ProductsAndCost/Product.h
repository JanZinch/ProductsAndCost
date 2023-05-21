#pragma once
#include "Money.h"

class Product
{

private:

    int code_;
    char _name[30];
    Money _cost;
    int _count;
    
public:

    Product();
    Product(const char *, Money, int);
    Product(const Product&);
    friend ostream& operator<<(ostream&, const Product&);
};
