#pragma once
#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

class ProductStore
{

private:

    fstream _database;
    string _databasePath;
    list<Product> _products;

    void ClearRdbufIfNeed();
    
public:
    
    ProductStore(string);

    void PrintAllProducts();
    Product* CreateProduct();
    void EditProduct();
    void RemoveProduct();


    
    
};
