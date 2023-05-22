#include "ProductStore.h"
#include <conio.h>

using namespace ProductsLogic;

int main(int argc, char* argv[])
{
    try
    {
        ProductStore productStore("DataBase.txt");
        bool needToExit = false;
        
        while (!needToExit)
        {
            cout << "1. View all products\n"
                "2. Add product\n"
                "3. Edit product\n"
                "4. Remove product\n"
                "0. Exit\n";
        
            switch (_getch())
            {

            case '1':
                productStore.PrintAllProducts();
                break;
        
            case '2':
                productStore.CreateProduct();
                break;

            case '3':
                productStore.EditProduct();
                break;
                
            case '4':
                productStore.TryRemoveProduct();
                break;

            case '0':
                needToExit = true;
                break;

            default:
                break;
            }
        }
        
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
