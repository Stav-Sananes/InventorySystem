#include <iostream>
#include <vector>
#include "DatabaseManager.h"
#include "Product.h"
#include "Config.h" 
using namespace std;
void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
template <typename T>
T getValidInput(const string& prompt, const string& errorMsg) {
    T input;
    while (true) {
        cout << prompt;
        cin >> input;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        else {
            cout << errorMsg << endl;
            clearInputStream();
        }
    }
}
void showMenu() {
    cout << "\n===== Inventory System Menu =====" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Update Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. View All Products" << endl;
    cout << "5. Exit" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    DatabaseManager dbManager(Config::host, Config::user, Config::password, Config::database);
    int choice = 0;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            string name;
            int id = getValidInput<int>("Enter product ID to update: ", "Invalid input for id number! Please enter a valid number.");
            cin >> id;
            cout << "Enter product name: ";
            cin.ignore(); // Clear the buffer before getline
            getline(cin, name);
            int quantity = getValidInput<int>("Enter new product quantity: ", "Invalid input for quantity number! Please enter a valid number.");
            int price = getValidInput<double>("Enter new product price: ", "Invalid input for price number! Please enter a valid number.");
            Product product(id, name, quantity, price);
            dbManager.addProduct(product);
            break;
        }

        case 2: {
            string name;
            int id = getValidInput<int>("Enter product ID to update: ", "Invalid input for id number! Please enter a valid number.");
            cout << "Enter new product name: ";
            cin.ignore(); 
            getline(cin, name);
            int quantity = getValidInput<int>("Enter new product quantity: ", "Invalid input for quantity number! Please enter a valid number.");
            int price = getValidInput<double>("Enter new product price: ", "Invalid input for price number! Please enter a valid number.");
            Product product(id, name, quantity, price);
            dbManager.updateProduct(product);
            break;
        }

        case 3: {
            int id = getValidInput<int>("Enter product ID to update: ", "Invalid input for id number! Please enter a valid number.");
            dbManager.deleteProduct(id);
            break;
        }

        case 4: {
            vector<Product> products = dbManager.getAllProducts();
            cout << "\n===== All Products =====" << endl;
            for (const Product& product : products) {
                cout << "ID: " << product.getID() << ", Name: " << product.getName()
                    << ", Quantity: " << product.getQuantity() << ", Price: " << product.getPrice() << endl;
            }
            break;
        }

        case 5: {
            cout << "Exiting the program..." << endl;
            break;
        }
        

        default:
            clearInputStream();
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
