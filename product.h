
#pragma once

#include <iostream>
using namespace std;

class Product{
public: 
      int id;
      string name;
      double price;
      int quantity;

      void display() const;
};