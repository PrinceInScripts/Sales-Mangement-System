#pragma once 

#include <iostream>

class Customer {
    public:
          int id;
          std::string name;
          std::string contactDetails;

          void display() const;
};