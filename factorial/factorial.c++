#include <iostream>

int main() { //factorial of a non-negative integer
    unsigned int factorial = 1;
    int number;

    std::cout << "Enter a non-negative integer: ";
    std::cin >> number;

    if (number < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    } else {
        for (int i = 1; i <= number; ++i) {
            factorial = factorial * i;
        }
    std::cout << "The factorial of " << number << " is: " << factorial << std::endl;
    }
}