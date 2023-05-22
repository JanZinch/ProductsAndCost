#include "ProductStore.h"

void ProductStore::ConsoleUtility::ClearRdbufIfNeed()
{
    if (cin.rdbuf()->in_avail() != 0) {

        cin.clear();
        cin.ignore(10, '\n');
    }
}

Product* ProductStore::ConsoleUtility::ReadProduct()
{
    string nameBuffer;
    int countBuffer;
    float unitCostBuffer;

    int progress = 0;
    const int maxSteps = 3;
    
    while (progress != -1 && progress < maxSteps)
    {
        ClearRdbufIfNeed();
            
        if (progress < 1)
        {
            cout << "Enter name of the product: " << endl;
            
            getline(cin, nameBuffer);

            if (nameBuffer == "undo")
            {
                progress = -1;
                break;
            }
        
            progress++;
        }
        
        if (progress < 2)
        {
            cout << "Enter the cost of unit: " << endl;
            cin >> unitCostBuffer;

            if (!cin)
            {
                cout << "Incorrect input!" << endl;
                continue;
            }
            else if (unitCostBuffer < 0.0f)
            {
                cout << "Cost can not be negative." << endl;
                continue;
            }

            progress++;
        }
        
        if (progress < 3)
        {
            cout << "Enter product count: " << endl;
            cin >> countBuffer;

            if (!cin)
            {
                cout << "Incorrect input!" << endl;
                continue;
            }
            else if (countBuffer < 0)
            {
                cout << "Count can not be negative." << endl;
                continue;
            }

            progress++;
        }
    }

    ClearRdbufIfNeed();
        
    if (progress >= maxSteps)
    {
        return new Product(nameBuffer.c_str(), Money(unitCostBuffer, "USD"), countBuffer); 
    }
    else
    {
        return nullptr;
    }
}


ProductStore::ProductStore(string databasePath)
{
    _databasePath = databasePath;
    _products = map<int, Product>();
    
    _database.open(_databasePath, fstream::in | fstream::binary);

    if(_database.is_open())
    {
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

int ProductStore::GenerateProductCode() const
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
    
    return generatedCode;
}

void ProductStore::PrintAllProducts() const
{
    int i = 0;
    cout << "Products: " << endl;

    for (pair<int, Product> codeProductPair : _products)
    {
        cout << i << ". " << "Code: " << codeProductPair.first << " " << codeProductPair.second << endl;
        i++;
    }
    
    cout << "End." << endl;
}

void ProductStore::CreateProduct()
{
    _database.open(_databasePath, fstream::out | fstream::app | fstream::binary);

    if (_database.is_open()) {
        
        Product* createdProduct = ConsoleUtility::ReadProduct();

        if (createdProduct != nullptr)
        {
            pair<int, Product> codeProductPair = pair<int, Product>(GenerateProductCode(), *createdProduct);
            _database.write((char*)&codeProductPair, sizeof(pair<int, Product>));
            _products.emplace(codeProductPair);
            
            cout << "Product was successfully created." << endl;

            delete createdProduct;
            createdProduct = nullptr;
        }
        else
        {
            cout << "Creation canceled." << endl;
        }
        
        _database.close();
    }
    else
    {
        throw exception("Incorrect database path.");
    }
}

void ProductStore::EditProduct()
{
    cout << "Enter code of the product: " << endl;
    int productCode;

    ConsoleUtility::ClearRdbufIfNeed();
        
    if (cin >> productCode)
    {
        const auto it = _products.find(productCode);

        if (it != _products.end())
        {
            Product* editableProduct = ConsoleUtility::ReadProduct();

            if (editableProduct != nullptr)
            {
                it->second = Product(*editableProduct);

                _database.open(_databasePath, fstream::out | fstream::trunc | fstream::binary);
                
                if (_database.is_open())
                {
                    for (pair<int, Product> codeProductPair : _products)
                    {
                        _database.write((char*)&codeProductPair, sizeof(pair<int, Product>));
                    }
                
                    _database.close();

                    cout << "Product successfully updated." << endl;
                }
                else
                {
                    throw exception("Incorrect database path.");
                }
            }
            else
            {
                cout << "Creation canceled." << endl;
            }
        }
        else
        {
            cout << "Product with this code don't exists." << endl;
        }
    }
    else
    {
        cout << "Incorrect input." << endl;
    }

    ConsoleUtility::ClearRdbufIfNeed();
}

void ProductStore::TryRemoveProduct()
{
    cout << "Enter code of the product: " << endl;
    int productCode;

    ConsoleUtility::ClearRdbufIfNeed();
        
    if (cin >> productCode)
    {
        int removesCount = _products.erase(productCode);

        if (removesCount > 0)
        {
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
                throw exception("Incorrect database path.");
            }
        }
        else
        {
            cout << "Product with this code don't exists." << endl;
        }
    }
    else
    {
        cout << "Incorrect input." << endl;
    }

    ConsoleUtility::ClearRdbufIfNeed();
}
