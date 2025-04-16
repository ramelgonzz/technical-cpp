#include <iostream>
#include <vector> //for dynamic input of velocities

int main() {
    int n;
    std::cout << "Enter the number of data points (velocities): ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Invalid number of data points." << std::endl;
        return 1;
    }

    std::vector<double> velocities(n);
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter velocity #" << (i + 1) << ": ";
        std::cin >> velocities[i];
        sum += velocities[i];
    }

    double average = sum / n;

    std::cout << "\nVelocities entered: ";
    for (double v : velocities) {
        std::cout << v << " ";
    }

    std::cout << "\nAverage velocity: " << average << std::endl;

    return 0;
}