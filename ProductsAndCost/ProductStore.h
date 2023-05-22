#pragma once
#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

namespace ProductsLogic
{
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
    
        int GenerateProductCode() const;
    
    public:
    
        ProductStore(string);
        void PrintAllProducts() const;
        void CreateProduct();
        void EditProduct();
        void TryRemoveProduct();
        
    };
}

