#include "ProductStore.h"

#include <conio.h>


int main(int argc, char* argv[])
{
    ProductStore productStore = ProductStore("DataBase.txt");
    bool needToExit = false;
    
    while(!needToExit)
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
            //productStore.CreateProduct();
            break;
        case '4':
            //productStore.CreateProduct();
            break;

        case '0':
            needToExit = true;
            break;
        
            /*default:
                break;*/
        
        }


        
    }

    
    

    


    
    return 0;
}
