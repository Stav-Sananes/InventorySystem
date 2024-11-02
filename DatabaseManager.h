#pragma once
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include "Product.h"
#include <memory>
#include <vector>

class DatabaseManager {
private:
    sql::mysql::MySQL_Driver* driver;
    std::unique_ptr<sql::Connection> conn;

public:
    DatabaseManager(const std::string& host, const std::string& user, const std::string& password, const std::string& db);
    void addProduct(const Product& product);
    void updateProduct(const Product& product);
    void deleteProduct(int productID);
    std::vector<Product> getAllProducts();
    ~DatabaseManager();
};

#endif 
