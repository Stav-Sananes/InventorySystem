#include "Product.h"

Product::Product(int id, const string& name, int qty, double price)
    : productID(id), name(name), quantity(qty), price(price) {}

int Product::getID() const { return productID; }
string Product::getName() const { return name; }
int Product::getQuantity() const { return quantity; }
double Product::getPrice() const { return price; }
void Product::setQuantity(int qty) { quantity = qty; }
void Product::setPrice(double price) { this->price = price; }
