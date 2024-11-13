#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//-------------------------------------------Number of items on the menu-------------------------------------

const int MENU_SIZE = 8;

void displayMenu(const string menuItems[], const double prices[], const int stock[]) {
    cout << "\n COFFEE MENU \n\n";
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << i + 1 << ". " << menuItems[i] << " Rs " << fixed << setprecision(2) << prices[i] << " (Available : " << stock[i] << ") \n";
    }
}

//-------------------------------------------Function to take an order------------------------------------------

void takeOrder(int choice, int quantity, string menuItems[], double prices[], int stock[], double& total) {
    if (stock[choice - 1] >= quantity) {
        total += prices[choice - 1] * quantity; // Add to total
        cout << quantity << " " << menuItems[choice - 1] << "(s) added to your order.\n";
        stock[choice - 1] -= quantity; // Decrease the stock
    } else {
        cout << "Sorry, we only have " << stock[choice - 1] << " left in stock\n";
    }
}

//------------------------------------------Function to display the total bill-----------------------------------------

void displayBill(double total) {
    cout << "\n Your Bill \n";
    cout << "Total amount : Rs " << fixed << setprecision(2) << total << endl;
    cout << "Thank you for your purchase!\n";
}

//----------------------------------------------Display available stock-----------------------------------------

void manageInventory(const string menuItems[], const int stock[]) {
    cout << "\n Inventory Management\n \n";
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << menuItems[i] << " Available Stock : " << stock[i] << endl;
    }
}

//-----------------------------------------------Function to save order to CSV-------------------------------------

void saveOrderToCSV(const string& customerName, double total) {
    ofstream file("orders.csv", ios::app); // Open in append mode

    if (file.is_open()) {
        file << customerName << "," << total << "\n"; // Save customer name and total amount
        file.close();
        cout << "Order saved successfully.\n";
    } else {
        cerr << "Unable to open file for writing\n";
    }
}

//-----------------------------------------------Function to read orders from CSV-------------------------------------

void readOrdersFromCSV() {
    ifstream file("orders.csv");
    string line;

    cout << "\n Previously saved orders:\n";
    cout << "Name,Total Amount\n";

    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl; // Display each line from the CSV
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading\n";
    }
}

//-----------------------------------------------Starting main functions-------------------------------------------

int main() {
    //\/\/\/menu items prices and stock quantities/\/\/\/\/\/\/\/\//
    string menuItems[MENU_SIZE] = {"Plane Tea", "Lankan Special Tea", "Mocha", "Cappuccino", "Americano", "Milk Cappuccino", "Coffee .co Tea", "Choco latte"};
    double prices[MENU_SIZE] = {80.00, 125.00, 400.00, 490.00, 550.00, 520.00, 300.00, 330.00};
    int stock[MENU_SIZE] = {30, 20, 10, 10, 20, 9, 12, 8};

    double total = 0.0;  //Total cost of the order
    int choice, quantity;
    bool isRunning = true;

    cout << " Welcome to the AURA TEA CAFE \n";

    //--------------------------------Handle ordering and inventory

    while (isRunning) {
        cout << "\n1. Order Coffee\n";
        cout << "2. View Inventory\n";
        cout << "3. View Previous Orders\n";
        cout << "4. Exit\n\n";
        cout << "Please select an option\n";
        cin >> choice;

        switch (choice) {
            case 1:
                // Ordering process
                while (true) {
                    displayMenu(menuItems, prices, stock);
                    cout << "\nSelect an item by number (1 -" << MENU_SIZE << ") or 0 to finish ordering : ";
                    cin >> choice;

                    if (choice == 0) break;

                    if (choice >= 1 && choice <= MENU_SIZE) {
                        cout << "Enter quantity : ";
                        cin >> quantity;

                        if (quantity > 0) {
                            takeOrder(choice, quantity, menuItems, prices, stock, total);
                        } else {
                            cout << "Invalid quantity, please enter a positive number\n";
                        }
                    } else {
                        cout << "Invalid choice, please enter a valid item\n";
                    }
                }

                // Display the final bill
                if (total > 0) {
                    displayBill(total);

                    // Ask for customer name and save order to CSV
                    string customerName;
                    cout << "Enter your name to save the order: ";
                    cin.ignore(); // Clear the newline from previous input
                    getline(cin, customerName);
                    saveOrderToCSV(customerName, total);
                } else {
                    cout << "No items ordered\n";
                }
                break;

            case 2: // Inventory management
                manageInventory(menuItems, stock);
                break;

            case 3: // View previous orders
                readOrdersFromCSV();
                break;

            case 4:
                cout << "Come Again. Have a great day\n";
                isRunning = false;
                break;

            default:
                cout << "Invalid option. Please try again\n";
                break;
        }
    }
    return 0;
}