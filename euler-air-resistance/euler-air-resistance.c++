#include <iostream>
#include <fstream>
#include <iomanip>

struct Vec2 {
    double x, y;
};

int main() {
    // Parameters
    double g = 9.81;           // gravity (m/s^2)
    double k = 0.1;            // drag coefficient per unit mass (1/s)
    double dt = 0.01;          // time step (s)
    double t = 0.0;            // time
    double totalTime = 5.0;    // simulate up to 5 seconds

    // Initial conditions
    Vec2 pos = {0.0, 0.0};               // starting at origin
    Vec2 vel = {20.0, 30.0};             // initial velocity (m/s)

    std::ofstream file("projectile_data.txt");
    if (!file) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    file << "# Time\tX\tY\n";
    file << std::fixed << std::setprecision(4);

    // Euler integration loop
    while (t <= totalTime && pos.y >= 0.0) {
        // Save current state
        file << t << "\t" << pos.x << "\t" << pos.y << "\n";

        // Compute acceleration
        Vec2 acc = {
            -k * vel.x,
            -g - k * vel.y
        };

        // Update velocity
        vel.x += acc.x * dt;
        vel.y += acc.y * dt;

        // Update position
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;

        // Advance time
        t += dt;
    }

    file.close();
    std::cout << "Simulation complete. Data saved to 'projectile_data.txt'.\n";
    return 0;
}
