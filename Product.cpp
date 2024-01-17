

#include "Product.h"
#include <iomanip>
using namespace std;

void Product::display() const{
     cout << "ID: " <<id << "\tName: " << name << "\tPrice: $" << fixed << setprecision(2) << price << "\tQuantity: " << quantity << endl;
}