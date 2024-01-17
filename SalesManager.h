#pragma once

#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"
#include "Order.h"

class SalesManager
{
private:
    std::vector<Product> products;
    std::vector<Customer> customers;
    std::vector<Order> orders;

    std::string dataFilePath;
    int pricePrecision;
    int quantityPrecision;

public:
    SalesManager();

    // Configuration functions
    void loadConfiguration();
    void saveConfiguration() const;

    // Product management functions
    void addProduct();
    void addProduct(const Product &product);
    void displayProducts() const;

    // Customer management functions
    void addCustomer();
    void addCustomer(const Customer &customer);
    void displayCustomers() const;

    // Order management functions
    void createOrder();
    void createOrder(const Order &order);
    void displayOrders() const;

    // Sales reporting function
    void generateSalesReport() const;

    // Data persistence functions
    void saveDataToFile() const;
    void loadDataFromFile();

    // Menu display function
    void displayMenu() const;

    // Utility functions
    bool isValidProductId(int productId, const std::vector<Product> &products);
    Product getProductById(int productId, const std::vector<Product> &products);
};