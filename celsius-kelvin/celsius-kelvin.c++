#include <iostream>

// constant
double kelvin = 273.15;

int main () { // converts celsius to kelvin
    double celsius;
    std::cout << "Convert Celsius to Kelvin" << std::endl;
    std::cout << "Enter Celsius" << std::endl;
    std::cin >> celsius;
    double k = celsius + kelvin;
    std::cout << "This converts to: " << k << " Kelvin." << std::endl;
    
    return 0;
}
