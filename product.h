
#pragma once

#include <iostream>


class Product{
public: 
      int id;
      std::string name;
      double price;
      int quantity;

      void display() const;
};