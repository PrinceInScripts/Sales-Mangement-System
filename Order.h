

#pragma once

#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"

class Order {
public:
    int orderId;
    Customer customer;
    std::vector<Product> products;

    double calculateTotalCost() const;
    void display() const;
};