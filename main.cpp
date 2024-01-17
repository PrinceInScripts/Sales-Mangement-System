
#include "SalesManager.h"

int main() {
    SalesManager salesManager;

    int choice;

    do {
        salesManager.displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                salesManager.addProduct();
                break;
            case 2:
                salesManager.displayProducts();
                break;
            case 3:
                salesManager.addCustomer();
                break;
            case 4:
                salesManager.displayCustomers();
                break;
            case 5:
                salesManager.createOrder();
                break;
            case 6:
                salesManager.displayOrders();
                break;
            case 7:
                salesManager.generateSalesReport();
                break;
            case 8:
                salesManager.saveConfiguration();
                std::cout << "Configuration saved.\n";
                break;
            case 9:
                salesManager.saveDataToFile();
                std::cout << "Data saved successfully.\n";
                break;
            case 10:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}