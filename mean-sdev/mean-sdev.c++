#include <iostream>
#include <cmath>  // for sqrt

double computeMean(double* data, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
        sum += data[i];
    return sum / size;
}

double computeStdDev(double* data, int size, double mean) {
    double variance = 0.0;
    for (int i = 0; i < size; ++i)
        variance += (data[i] - mean) * (data[i] - mean);
    variance /= (size - 1);  // sample standard deviation
    return std::sqrt(variance);
}

int main() {
    int n;
    std::cout << "Enter number of data points: ";
    std::cin >> n;

    if (n < 2) {
        std::cerr << "Need at least 2 data points.\n";
        return 1;
    }

    // Dynamic allocation
    double* data = new double[n];

    std::cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i)
        std::cin >> data[i];

    double mean = computeMean(data, n);
    double stddev = computeStdDev(data, n, mean);

    std::cout << "Mean = " << mean << "\n";
    std::cout << "Standard Deviation = " << stddev << "\n";

    delete[] data;  // Free memory
    return 0;
}
