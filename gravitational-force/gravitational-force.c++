#include <iostream>
#include <cmath>

// Formula F = G * m1 * m2 / r^2

// constant

const double G = 6.67430e-11; // Newtons Meters squared per Kilogram squared

// compute gravitational force

double gravitationalForce(double m1, double m2, double r) {
    if (r==0) {
        std::cerr << " Distance can't be zero " << std::endl;
        return 0;
    }
    return G * (m1 * m2) / (r * r);
}

// main equation to take parameter values

int main() {
    double mass1, mass2, distance;

    std::cout << "Enter mass 1 (kg): ";
    std::cin >> mass1;

    std::cout << "Enter mass 2 (kg): ";
    std::cin >> mass2;

    std::cout << "Enter distance between masses (m): ";
    std::cin >> distance;

    double force = gravitationalForce(mass1, mass2, distance);

    std::cout << "The gravitational force between the two masses is " << force << " Newtons " << std::endl;

    return 0;
}