

#include "SalesManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>

SalesManager::SalesManager()
{
    dataFilePath = "data.txt";
    pricePrecision = 2;
    quantityPrecision = 0;
    loadConfiguration();
}

void SalesManager::loadConfiguration()
{
    std::ifstream configFile("config.txt");

    if (!configFile.is_open())
    {
        std::cerr << "Warning: Configuration file not found.\n";
        return;
    }

    std::string line;
    int lineCount = 0;

    while (std::getline(configFile, line))
    {
        ++lineCount;
        std::istringstream iss(line);
        std::string key, value;
        if (iss >> key >> value)
        {
            try
            {
                if (key == "data_file")
                {
                    dataFilePath = value;
                }
                else if (key == "price_precision")
                {
                    pricePrecision = std::stoi(value);
                }
                else if (key == "quantity_precision")
                {
                    quantityPrecision = std::stoi(value);
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error in line " << lineCount << ": " << e.what() << "\n";
                // Add further error handling or exit the program as needed
            }
        }
    }

    configFile.close();
}
void SalesManager::saveConfiguration() const
{
    std::ofstream configFile("config.txt");

    if (!configFile.is_open())
    {
        std::cerr << "Error: Unable to open the configuration file for writing./n";
        return;
    }

    configFile << "#Configuration file for sales ManageMent System\n";
    configFile << "data_file = " << dataFilePath << "\n";
    configFile << "price_precision = " << pricePrecision << "\n";
    configFile << "quantity_precision = " << quantityPrecision << "\n";

    configFile.close();
}

// Product Mangement system

void SalesManager::addProduct()
{
    Product product;
    std::cout << "Enter Product Details:" << std::endl;
    std::cout << "ID: ";
    std::cin >> product.id;
    std::cout << "Name: ";
    std::cin >> product.name;
    std::cout << "Price: ";
    std::cin >> product.price;
    std::cout << "Quantity: ";
    std::cin >> product.quantity;

    addProduct(product);
}

void SalesManager::addProduct(const Product &product)
{
    products.push_back(product);
}

void SalesManager::displayProducts() const
{
    std::cout << "Product in Inventory: " << std::endl;
    for (const auto &product : products)
    {
        product.display();
    }
}

// Customer Mangement functions
void SalesManager::addCustomer()
{
    Customer customer;
    std::cout << "Enter Customer Details:" << std::endl;
    std::cout << "ID: ";
    std::cin >> customer.id;
    std::cout << "Name: ";
    std::cin >> customer.name;
    std::cout << "Contact Details: ";
    std::cin >> customer.contactDetails;

    addCustomer(customer);
}

void SalesManager::addCustomer(const Customer &customer)
{
    customers.push_back(customer);
}

void SalesManager::displayCustomers() const
{
    std::cout << "Customer List:" << std::endl;
    for (const auto &customer : customers)
    {
        customer.display();
    }
}

// Utiliy function
bool SalesManager::isValidProductId(int productId, const std::vector<Product> &products)
{
    return std::any_of(products.begin(), products.end(), [productId](const Product &p)
                       { return p.id == productId; });
}

Product SalesManager::getProductById(int productId, const std::vector<Product> &products)
{
    auto it = std::find_if(products.begin(), products.end(), [productId](const Product &p)
                           { return p.id == productId; });

    if (it != products.end())
    {
        return *it;
    }
    throw std::runtime_error("Product not found");
}

// Order Managmnet function

void SalesManager::createOrder()
{
    Order order;
    std::cout << "Enter Order Details:" << std::endl;
    std::cout << "Order ID: ";
    std::cin >> order.orderId;

    displayCustomers();
    std::cout << "Select Customer ID for the order: ";
    std::cin >> order.customer.id;

    displayProducts();
    int productChoice;
    do
    {
        Product product;
        std::cout << "Select Product ID to add to the order (0 to finish): ";
        std::cin >> productChoice;

        if (productChoice != 0 && isValidProductId(productChoice, products))
        {
            order.products.push_back(getProductById(productChoice, products));
        }
        else if (productChoice != 0)
        {
            std::cout << "Invalid Product ID. Please try again.\n";
        }
    } while (productChoice != 0);

    createOrder(order);
}

void SalesManager::createOrder(const Order &order)
{
    std::cout << "Order Created Successfully!" << std::endl;
    orders.push_back(order);
}

void SalesManager::displayOrders() const
{
    std::cout << "Orders:" << std::endl;
    for (const auto &order : orders)
    {
        order.display();
    }
}

// Sales reporting function
void SalesManager::generateSalesReport() const
{
    std::cout << "Sales Report:" << std::endl;

    // Calculate total revenue
    double totalRevenue = 0.0;
    for (const auto &order : orders)
    {
        for (const auto &product : order.products)
        {
            totalRevenue += product.price * product.quantity;
        }
    }

    std::cout << "Total Revenue: $" << std::fixed << std::setprecision(pricePrecision) << totalRevenue << std::endl;
}

// Data persisitance function
void SalesManager::saveDataToFile() const
{
    std::ofstream file(dataFilePath);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open the data file for writing.\n";
        return;
    }

    for (const auto &product : products)
    {
        file << "Product\t" << product.id << "\t" << product.name << "\t" << product.price << "\t" << product.quantity << std::endl;
    }

    for (const auto &customer : customers)
    {
        file << "Customer\t" << customer.id << "\t" << customer.name << "\t" << customer.contactDetails << std::endl;
    }

    for (const auto &order : orders)
    {
        file << "Order\t" << order.orderId << "\t" << order.customer.id << "\t";

        for (const auto &product : order.products)
        {
            file << product.id << "\t";
        }

        file << std::endl;
    }

    file.close();
}

void SalesManager::loadDataFromFile()
{
    std::ifstream file(dataFilePath);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open the data file for reading.\n";
        return;
    }

    // Clear existing data
    products.clear();
    customers.clear();
    orders.clear();

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Product")
        {
            Product product;
            iss >> product.id >> product.name >> product.price >> product.quantity;
            products.push_back(product);
        }
        else if (type == "Customer")
        {
            Customer customer;
            iss >> customer.id >> customer.name >> customer.contactDetails;
            customers.push_back(customer);
        }
        else if (type == "Order")
        {
            Order order;
            iss >> order.orderId >> order.customer.id;

            int productId;
            while (iss >> productId)
            {
                auto it = std::find_if(products.begin(), products.end(), [productId](const Product &p)
                                       { return p.id == productId; });

                if (it != products.end())
                {
                    order.products.push_back(*it);
                }
            }

            orders.push_back(order);
        }
    }

    file.close();
}

// Menu display function
void SalesManager::displayMenu() const
{
    std::cout << "Sales Management System Menu:" << std::endl;
    std::cout << "1. Add Product\n2. Display Products\n3. Add Customer\n4. Display Customers\n5. Create Order\n6. Display Orders\n7. Generate Sales Report\n8. Exit\n";
    std::cout << "Enter your choice: ";
}