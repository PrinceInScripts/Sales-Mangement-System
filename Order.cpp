

#include "Order.h"
#include <iomanip>


double Order::calculateTotalCost() const {
    double totalCost = 0;
    for (const auto& product : products) {
        totalCost += product.price;
    }
    return totalCost;
}

void Order::display() const {
    std::cout << "Order ID: " << orderId << "\tCustomer: " << customer.name << "\tTotal Cost: $" << std::fixed << std::setprecision(2) << calculateTotalCost() << std::endl;
    std::cout << "Products in the order:" << std::endl;
    for (const auto& product : products) {
        product.display();
    }
}