#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Potential energy function U(x) = x^2
double potential(double x) {
    return x * x;
}

int main() {
    const int numSamples = 1000000;  // number of random points
    const double xMin = 0.0, xMax = 1.0;
    const double yMin = 0.0, yMax = 1.0;  // bounding box for U(x) = x^2 on [0,1]

    std::srand(static_cast<unsigned int>(std::time(0)));

    int underCurve = 0;

    for (int i = 0; i < numSamples; ++i) {
        double x = xMin + (xMax - xMin) * (double(std::rand()) / RAND_MAX);
        double y = yMin + (yMax - yMin) * (double(std::rand()) / RAND_MAX);

        if (y <= potential(x)) {
            ++underCurve;
        }
    }

    double areaBox = (xMax - xMin) * (yMax - yMin);
    double estimatedArea = (double)underCurve / numSamples * areaBox;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Estimated area under U(x) = x^2 on [0, 1]: " << estimatedArea << "\n";
    std::cout << "Expected (analytical) area = 1/3 = " << 1.0/3.0 << "\n";

    return 0;
}
