#include <iostream>
#include <vector>
#include <algorithm>  // for std::sort
#include <iomanip>    // for std::setprecision

int main() {
    // Step 1: Store energy values in a vector
    std::vector<double> energyValues = {
        12.5, 3.1, 7.8, 9.0, 15.6, 4.4, 11.3
    };

    std::cout << "Original energy values:\n";
    for (double e : energyValues) {
        std::cout << std::fixed << std::setprecision(2) << e << " J\n";
    }

    // Step 2: Sort the vector
    std::sort(energyValues.begin(), energyValues.end());

    // Step 3: Display sorted values
    std::cout << "\nSorted energy values (ascending):\n";
    for (double e : energyValues) {
        std::cout << std::fixed << std::setprecision(2) << e << " J\n";
    }

    return 0;
}
