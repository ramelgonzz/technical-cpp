#include <iostream>

int main() {
    double initial_height = 1.0; // Initial height in meters
    double time_step = 0.1;        // Time increment in seconds
    double gravity = 9.81;         // Acceleration due to gravity in m/s^2
    double time = 0.0;             // Initial time
    double height = initial_height; // Current height

    std::cout << "Enter the initial height in meters" << std::endl;
    std::cin >> initial_height;

    std::cout << "Time (s)  Height (m)" << std::endl;

    for (int i = 0; height > 0; ++i) {
        std::cout.precision(4);
        std::cout << std::fixed << time << "       " << height << std::endl;
        time += time_step;
        height = initial_height - 0.5 * gravity * time * time;
    }

    return 0;
}