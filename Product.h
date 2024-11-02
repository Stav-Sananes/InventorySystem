#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
private:
    int productID;
    string name;
    int quantity;
    double price;

public:
    Product(int id, const string& name, int qty, double price);
    int getID() const;
    string getName() const;
    int getQuantity() const;
    double getPrice() const;

    void setQuantity(int qty);
    void setPrice(double price);
};

#endif
