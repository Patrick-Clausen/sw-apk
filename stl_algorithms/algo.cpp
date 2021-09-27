/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha & Tue                     */
/*****************************************/

#include <fstream>
#include <iostream>
#include <iterator>
#include <assert.h>

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>


#define PRODUCT_DB_FILE        "product.db"

template <class T, class Compare >
constexpr const T& clamp( const T& v, const T& lo , const T& hi , Compare
comp )
{
    return assert( !comp(hi , lo) ),
            comp(v, lo) ? lo : comp(hi , v) ? hi : v;
}

template <class T>
constexpr const T& clamp( const T& v, const T& lo , const T& hi )
{
    return :: clamp( v, lo , hi , std::less <>() );
}

class Product {
public:
    Product(const std::string &name, float price, unsigned int sold = 0)
            : name_(name), price_(price), sold_(sold) {}

    Product()
            : name_(""), price_(0), sold_(0) {}

    const std::string &name() const {
        return name_;
    }

    float price() const {
        return price_;
    }

    void setPrice(float newPrice) {
        price_ = newPrice;
    }

    unsigned int sold() const {
        return sold_;
    }

    void operator()(Product& p) {
        p.price_ *= 0.9;
    }

    friend std::istream &operator>>(std::istream &i, Product &p);

    friend std::ostream &operator<<(std::ostream &o, const Product &p);

private:
    std::string name_;
    float price_;
    int sold_;
};

typedef std::vector<Product> ProductList;


std::ostream &operator<<(std::ostream &o, const Product &p) {
    return o << p.name_ << " " << p.price_ << " " << p.sold_;
}

std::istream &operator>>(std::istream &i, Product &p) {
    return i >> p.name_ >> p.price_ >> p.sold_;
}


/**
 * Read products from file
 */
void productDBRead(ProductList &pl, const std::string &fileName) {
    pl.clear();
    std::ifstream pFile(fileName.c_str());

    std::istream_iterator<Product> sof(pFile);
    std::istream_iterator<Product> eof;

    std::copy(
            sof,
            eof,
            std::back_inserter(pl));
}


/**
 * Printout all products
 */
void printAll(const ProductList &pl) {

    std::ostream_iterator<Product> it(std::cout, "\n");

    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out all products..." << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::copy(pl.begin(), pl.end(), it);
    std::cout << "##################################################" << std::endl;
}


/**
   Add item
*/
/*
void addItem(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Enter product in format: NAME PRICE SOLD" << std::endl;
    std::istream_iterator<Product> it(std::cin);

    pl.push_back(*it);
}
 */
void addItem(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Input an item" << std::endl;
    std::istream_iterator<Product> cin_it(std::cin);
    std::istream_iterator<Product> eos;
    std::copy(cin_it, eos, back_inserter(pl));
    std::cin.clear();
    std::cout << "-------------" << std::endl;
}

/**
   Write data to db file
*/
void productDBWrite(const ProductList &pl, const std::string &fileName) {
    std::ofstream oFile(fileName.c_str());
    std::ostream_iterator<Product> it(oFile, "\n");

    std::copy(pl.begin(), pl.end(), it);
}


/**
 * Print poorly selling products
 */


void printPoorlySellingProducts(const ProductList &pl) {
    std::ostream_iterator<Product> it(std::cout, "\n");

    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out poorly selling products..." << std::endl;
    std::remove_copy_if(pl.begin(), pl.end(), it, [](Product p) -> bool
    {
        return p.sold() >= 10;
    });
    std::cout << "----------------------------" << std::endl;
    std::cout << "##################################################" << std::endl;
}


/**
 * Set a discount on all products - Using for_each()
 */
void addDiscountUsingForEach(ProductList &pl) {
    std::for_each(pl.begin(), pl.end(), Product());
}


/**
 * Set a discount on all products - Using transform()
 */
void addDiscountUsingTransform(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    std::cout << "Enter desired discount in percentage between 10 and 90: ";
    std::istream_iterator<int> iit(std::cin);
    std::ostream_iterator<Product> oit(std::cout, "\n");
    std::transform(pl.begin(),pl.end(),oit,[&iit](Product p) -> Product{
        p.setPrice(p.price()*(1-float(clamp((*iit), 10, 90))/100.));
        return p;
    });
    std::cout << "----------------------------" << std::endl;
    std::cout << "##################################################" << std::endl;
}


/**
 * Calculate the total amount of sold products
 */
void calcTotalSoldProducts(ProductList &pl) {
    std::cout << "##################################################" << std::endl;
    unsigned int total = std::accumulate(pl.begin(),pl.end(), 0, [](unsigned int acc, Product& p) -> unsigned int {
        return acc + p.sold();
    });
    std::cout << "Total products sold: " << total << std::endl;
    std::cout << "##################################################" << std::endl;
}


/**
 * Setting discount using bind2nd - OPTIONAL
 */



