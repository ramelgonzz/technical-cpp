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
    Vector2D position;
    Vector2D velocity;

    Particle(Vector2D pos = {}, Vector2D vel = {}) : position(pos), velocity(vel) {}

    void update(double dt) {
        position = position + velocity * dt;
    }
};

int main() {
    const int numParticles = 3;
    const double dt = 1.0;  // time step

    // Dynamically allocate array of Particle objects
    Particle* particles = new Particle[numParticles] {
        { {0, 0}, {1, 1} },
        { {10, 5}, {-0.5, 0.2} },
        { {3, -2}, {0.1, 0.3} }
    };

    // Use pointers to iterate and update
    std::cout << "Initial Positions:\n";
    for (int i = 0; i < numParticles; ++i) {
        std::cout << "Particle " << i << ": ";
        (particles + i)->position.print();
        std::cout << "\n";
    }

    // Simulate one update step
    for (int i = 0; i < numParticles; ++i) {
        Particle* p = particles + i;
        p->update(dt);
    }

    std::cout << "\nAfter " << dt << "s:\n";
    for (int i = 0; i < numParticles; ++i) {
        std::cout << "Particle " << i << ": ";
        (particles + i)->position.print();
        std::cout << "\n";
    }

    // Clean up
    delete[] particles;

    return 0;
}
