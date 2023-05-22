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
    map<int, Product> _products;
    
    class ConsoleUtility
    {
    public:
        static void ClearRdbufIfNeed();
        static Product* ReadProduct();
    };
    
    int GenerateProductCode();
    
public:
    
    ProductStore(string);
    void PrintAllProducts();
    void CreateProduct();
    void EditProduct();
    void TryRemoveProduct();


    
    
};
