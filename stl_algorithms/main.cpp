#include <vector>
#include <algorithm>

#include "wrapper.cpp"

int main() {
    /* 4.1
    Test t;

    Wrapper<int> w(std::bind(&Test::printExt, t, std::placeholders::_1));
    std::vector<int> v({1, 3, 4, 6, 8});

    std::copy(v.begin(), v.end(), w);
    */
    // ¤.2
    Test t;
    std::vector<int> v({1, 3, 4, 6, 8});

    std::for_each(v.begin(), v.end(), [t](int e) -> void {
        t.printExt(e);
    });


    return 0;
}

/*
#include "algo.cpp"

int main() {
    bool running = true;
    ProductList pl;

    while (running) {
        char choice;

        std::cout << "********************" << std::endl;
        std::cout << "Help menu: " << std::endl;
        std::cout << "'1' Read product database" << std::endl;
        std::cout << "'2' Print all items" << std::endl;
        std::cout << "'3' Add item" << std::endl;
        std::cout << "'4' Write product database" << std::endl;
        std::cout << "'5' Print poorly selling products" << std::endl;
        std::cout << "'6' Set a discount on all products (using for_each() )" << std::endl;
        std::cout << "'7' Set a discount on all products (using transform() )" << std::endl;
        std::cout << "'8' Calculate the total amount of sold products" << std::endl;


        std::cout << "'q' Quit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                productDBRead(pl, PRODUCT_DB_FILE);
                break;

            case '2':
                printAll(pl);
                break;

            case '3':
                addItem(pl);
                break;

            case '4':
                productDBWrite(pl, PRODUCT_DB_FILE);
                break;

            case '5':
                printPoorlySellingProducts(pl);
                break;

            case '6':
                addDiscountUsingForEach(pl);
                break;

            case '7':
                addDiscountUsingTransform(pl);
                break;

            case '8':
                calcTotalSoldProducts(pl);
                break;

            case 'q':
            case 'Q':
                running = false;
        }


    }
}
 */