#include "Customer.h"

void Customer::display() const{
    std::cout<< "ID: " <<id << "\tName: " << name << "\tContact: "<<contactDetails << std::endl;
}