#pragma once
#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

class ProductStore
{

private:

    fstream _database;
    string _databasePath;
    //list<Product> _products;
    map<int, Product> _products;

    
    void ClearRdbufIfNeed();
    int GenerateProductCode();
    
public:
    
    ProductStore(string);
    void PrintAllProducts();
    Product* CreateProduct();
    void EditProduct();
    void RemoveProduct();


    
    
};
