#include "DatabaseManager.h"
#include <string>
#include <iostream>
using namespace std;
DatabaseManager::DatabaseManager(const string& host, const string& user, const string& password, const string& db) {
    driver = sql::mysql::get_mysql_driver_instance();
    conn = unique_ptr<sql::Connection>(driver->connect(host, user, password));
    conn->setSchema(db);
}

DatabaseManager::~DatabaseManager() {
    conn->close();
}

void DatabaseManager::addProduct(const Product& product) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO products (id, name, quantity, price) VALUES (?, ?, ?, ?)"));
        pstmt->setInt(1, product.getID());
        pstmt->setString(2, product.getName());
        pstmt->setInt(3, product.getQuantity());
        pstmt->setDouble(4, product.getPrice());
        pstmt->executeUpdate();
        cout << "Product added successfully." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void DatabaseManager::updateProduct(const Product& product) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("UPDATE products SET name = ?, quantity = ?, price = ? WHERE id = ?"));
        pstmt->setString(1, product.getName());
        pstmt->setInt(2, product.getQuantity());
        pstmt->setDouble(3, product.getPrice());
        pstmt->setInt(4, product.getID());
        pstmt->executeUpdate();
        cout << "Product updated successfully." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void DatabaseManager::deleteProduct(int productID) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("DELETE FROM products WHERE id = ?"));
        pstmt->setInt(1, productID);
        pstmt->executeUpdate();
        cout << "Product deleted successfully." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

vector<Product> DatabaseManager::getAllProducts() {
    vector<Product> products;
    try {
        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name, quantity, price FROM products"));

        while (res->next()) {
            Product product(res->getInt("id"), res->getString("name"), res->getInt("quantity"), res->getDouble("price"));
            products.push_back(product);
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }

    return products;
}
