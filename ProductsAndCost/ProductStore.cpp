#include "ProductStore.h"

void ProductStore::ConsoleUtility::ClearRdbufIfNeed()
{
    if (cin.rdbuf()->in_avail() != 0) {

        cin.clear();
        cin.ignore(10, '\n');
    }
}


ProductStore::ProductStore(string databasePath)
{
    _databasePath = databasePath;
    //_products = list<Product>();
    _products = map<int, Product>();
    
    _database.open(_databasePath, fstream::in | fstream::binary);

    if(_database.is_open())
    {
        /*Product productBuffer;

        while (_database.read((char*)&productBuffer, sizeof(Product))) {

            _products.push_back(productBuffer);
        }*/
        

        pair<int, Product> codeProductPair;
        
        while (_database.read((char*)&codeProductPair, sizeof(pair<int, Product>))) {

            _products.emplace(codeProductPair);
        }
        
        _database.close();
    }
    else
    {
        throw exception("Incorrect database path.");
    }
}

int ProductStore::GenerateProductCode()
{
    srand(time(nullptr));
    int generatedCode = rand() % 900 + 100;

    for (pair<int, Product> codeProductPair : _products)
    {
        if (codeProductPair.first == generatedCode)
        {
            generatedCode = GenerateProductCode();
            break;
        }
    }

    cout<<"CODE: " << generatedCode << endl;
    
    return generatedCode;
}

void ProductStore::PrintAllProducts()
{
    int i = 0;
    cout << "Products: " << endl;
    
    /*for (Product product : _products)
    {
        cout << i << ". " << product << endl;
        i++;
    }*/

    for (pair<int, Product> codeProductPair : _products)
    {
        cout << i << ". " << "Code: " << codeProductPair.first << " " << codeProductPair.second << endl;
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
            ConsoleUtility::ClearRdbufIfNeed();
            
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
        
        ConsoleUtility::ClearRdbufIfNeed();
        
        if (progress >= maxSteps)
        {
            Product crated_product = Product(name_buffer.c_str(), Money(unit_cost_buffer, "USD"), count_buffer);
            //_database.write((char*)&crated_product, sizeof(Product));	

            pair<int, Product> codeProductPair = pair<int, Product>(GenerateProductCode(), crated_product);

            _database.write((char*)&codeProductPair, sizeof(pair<int, Product>));
            
            //_products.push_back(crated_product);
            _products.emplace(codeProductPair);
            
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

void ProductStore::TryRemoveProduct()
{
    try
    {
        cout << "Enter code of the product: " << endl;
        int productCode;

        ConsoleUtility::ClearRdbufIfNeed();
        
        if (cin >> productCode)
        {
            _products.erase(productCode);
            
            _database.open(_databasePath, fstream::out | fstream::trunc | fstream::binary);

            if (_database.is_open())
            {
                for (pair<int, Product> codeProductPair : _products)
                {
                    _database.write((char*)&codeProductPair, sizeof(pair<int, Product>));
                }
                
                _database.close();

                cout << "Product successfully removed." << endl;
            }
            else
            {
                exit(EXIT_FAILURE);
            }
            
        }
        else
        {
            cout << "Incorrect input." << endl;
        }

        ConsoleUtility::ClearRdbufIfNeed();
        
    }
    catch (exception &ex)
    {
        cout << "Product with this code don't exists." << endl;
    }

    

    
}
