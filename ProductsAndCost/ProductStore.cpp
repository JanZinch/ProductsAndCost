#include "ProductStore.h"

void ProductStore::ClearRdbufIfNeed()
{
    if (cin.rdbuf()->in_avail() != 0) {

        cin.clear();
    }
}

ProductStore::ProductStore(string databasePath)
{
    _databasePath = databasePath;
    _products = list<Product>();
    
    _database.open(_databasePath, fstream::in | fstream::binary);

    if(_database.is_open())
    {
        Product productBuffer;

        while (_database.read((char*)&productBuffer, sizeof(Product))) {

            _products.push_back(productBuffer);
        }

        _database.close();
    }
    else
    {
        throw exception("Incorrect database path.");
    }
}

void ProductStore::PrintAllProducts()
{
    int i = 0;
    cout << "Products: " << endl;
    
    for (Product product : _products)
    {
        cout << i << ". " << product << endl;
        i++;
    }
    cout << "End." << endl;
    
}

Product* ProductStore::CreateProduct()
{
    string name_buffer;
    int count_buffer;
    float unit_cost_buffer;

    int progress = 0;
    const int maxSteps = 3;
    
    _database.open(_databasePath, fstream::out | fstream::app | fstream::binary);

    if (_database.is_open()) {

        while (progress != -1 && progress < maxSteps)
        {
            ClearRdbufIfNeed();
        
            if (progress < 1)
            {
                cout << "Enter name of the product: " << endl;
            
                getline(cin, name_buffer);

                if (name_buffer == "undo")
                {
                    progress = -1;
                    break;
                }
        
                progress++;
            }
        
            if (progress < 2)
            {
                cout << "Enter product count: " << endl;
                cin >> count_buffer;

                if (!cin)
                {
                    cout << "Incorrect input!" << endl;
                    break;
                }
                else if(count_buffer < 0)
                {
                    cout << "Count can not be negative." << endl;
                    break;
                }

                progress++;
            
            }
        
            if (progress < 3)
            {
                cout << "Enter the cost of unit: " << endl;
                cin >> unit_cost_buffer;

                if (!cin)
                {
                    cout << "Incorrect input!" << endl;
                    break;
                }
                else if(unit_cost_buffer < 0.0f)
                {
                    cout << "Cost can not be negative." << endl;
                    break;
                }

                progress++;
            }
        }

        if (progress >= maxSteps)
        {
            Product crated_product = Product(name_buffer.c_str(), Money(unit_cost_buffer, "USD"), count_buffer);
            _database.write((char*)&crated_product, sizeof(Product));	

            _products.push_back(crated_product);
            
            cout << "Product was successfully created." << endl;
            
            _database.close();
            return &crated_product; 
        }
        else
        {
            _database.close();
            return nullptr;
        }
    }
    else
    {
        _database.close();
        return nullptr;
    }
    
}
