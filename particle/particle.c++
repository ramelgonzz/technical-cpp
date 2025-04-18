#include <iostream>

struct Vector2D {
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

class Particle {
public:
    double mass;
    Vector2D position;
    Vector2D velocity;

    Particle(double m, Vector2D pos, Vector2D vel)
        : mass(m), position(pos), velocity(vel) {}

    void updatePosition(double dt) {
        position = position + velocity * dt;
    }

    void printState() const {
        std::cout << "Mass: " << mass << " kg\n";
        std::cout << "Position: "; position.print(); std::cout << "\n";
        std::cout << "Velocity: "; velocity.print(); std::cout << "\n";
    }
};

int main() {
    Particle p(2.0, {0.0, 0.0}, {1.0, 1.5}); // mass, position, velocity

    std::cout << "Initial State:\n";
    p.printState();

    double dt = 1.0; // time step in seconds
    p.updatePosition(dt);

    std::cout << "\nAfter " << dt << "s:\n";
    p.printState();

    return 0;
}
