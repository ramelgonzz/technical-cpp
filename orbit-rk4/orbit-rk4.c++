#include <iostream>
#include <fstream>
#include <cmath>

// Compile and run, then plot with:
// gnuplot -e "plot 'orbit-output.txt' using 2:3 with lines title 'Orbit'; pause -1"

const double G = 6.67430e-11; // gravitational constant
const double M = 1.989e30;    // mass of central body (e.g., Sun)

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2D operator/(double scalar) const {
        return {x / scalar, y / scalar};
    }

    double norm() const {
        return std::sqrt(x * x + y * y);
    }
};

class Planet {
public:
    Vector2D position;
    Vector2D velocity;

    Planet(Vector2D pos, Vector2D vel) : position(pos), velocity(vel) {}

    Vector2D acceleration() const {
        double r = position.norm();
        double factor = -G * M / (r * r * r);
        return position * factor;
    }

    void integrateRK4(double dt) {
        Vector2D k1_v = acceleration();
        Vector2D k1_r = velocity;

        Vector2D k2_v = accelerationFrom(position + k1_r * (dt / 2.0));
        Vector2D k2_r = velocity + k1_v * (dt / 2.0);

        Vector2D k3_v = accelerationFrom(position + k2_r * (dt / 2.0));
        Vector2D k3_r = velocity + k2_v * (dt / 2.0);

        Vector2D k4_v = accelerationFrom(position + k3_r * dt);
        Vector2D k4_r = velocity + k3_v * dt;

        position = position + (k1_r + k2_r * 2.0 + k3_r * 2.0 + k4_r) * (dt / 6.0);
        velocity = velocity + (k1_v + k2_v * 2.0 + k3_v * 2.0 + k4_v) * (dt / 6.0);
    }

private:
    Vector2D accelerationFrom(const Vector2D& pos) const {
        double r = pos.norm();
        double factor = -G * M / (r * r * r);
        return pos * factor;
    }
};

int main() {
    const double dt = 60.0; // time step in seconds
    const int steps = 100000;

    // Initial state: 1 AU from sun, circular orbit speed
    Planet earth({1.496e11, 0.0}, {0.0, 29780.0});

    std::ofstream file("orbit-output.txt");
    if (!file) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    for (int i = 0; i < steps; ++i) {
        file << i * dt << '\t' << earth.position.x << '\t' << earth.position.y << '\n';
        earth.integrateRK4(dt);
    }

    file.close();
    std::cout << "Simulation complete. Data saved to 'orbit-output.txt'\n";
    return 0;
}
