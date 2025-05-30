#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Templated function to compute Euclidean norm of a 3D vector
template<typename T>
T vectorNorm(T x, T y, T z) {
    return std::sqrt(x * x + y * y + z * z);
}

// Struct to represent a 3D particle
template<typename T>
struct Particle {
    T x, y, z;

    // Compute distance to another particle
    T distanceTo(const Particle<T>& other) const {
        return vectorNorm(x - other.x, y - other.y, z - other.z);
    }
};

int main() {
    std::vector<Particle<double>> particles = {
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 2.0, 0.0},
        {0.0, 0.0, 3.0}
    };

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Distances between particles:\n";

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            double dist = particles[i].distanceTo(particles[j]);
            std::cout << "Particle " << i << " <-> Particle " << j
                      << " = " << dist << "\n";
        }
    }

    return 0;
}
