#include <iostream>
#include <cmath>

const double k_e = 8.9875517923e9; // Coulomb constant in N·m²/C²

struct Vector2D {
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

    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D normalized() const {
        double mag = magnitude();
        return (mag != 0) ? (*this * (1.0 / mag)) : Vector2D(0, 0);
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

    virtual ~Particle() = default;

    void updatePosition(double dt) {
        position = position + velocity * dt;
    }

    virtual void printState() const {
        std::cout << "Mass: " << mass << " kg\n";
        std::cout << "Position: "; position.print(); std::cout << "\n";
        std::cout << "Velocity: "; velocity.print(); std::cout << "\n";
    }
};

class ChargedParticle : public Particle {
public:
    double charge; // in Coulombs

    ChargedParticle(double m, double q, Vector2D pos, Vector2D vel)
        : Particle(m, pos, vel), charge(q) {}

    Vector2D electricForceFrom(const ChargedParticle& other) const {
        Vector2D r = other.position - position;
        double distance = r.magnitude();
        if (distance == 0) return Vector2D(0, 0); // Avoid division by zero
        double forceMagnitude = k_e * (charge * other.charge) / (distance * distance);
        return r.normalized() * forceMagnitude;
    }

    void printState() const override {
        Particle::printState();
        std::cout << "Charge: " << charge << " C\n";
    }
};

int main() {
    ChargedParticle p1(1.0, 1e-6, {0, 0}, {0, 0});    // 1 μC
    ChargedParticle p2(1.0, -2e-6, {0.03, 0}, {0, 0}); // -2 μC, 3 cm away

    std::cout << "Particle 1:\n"; p1.printState(); std::cout << "\n";
    std::cout << "Particle 2:\n"; p2.printState(); std::cout << "\n";

    Vector2D force = p1.electricForceFrom(p2);
    std::cout << "\nElectric Force on Particle 1 due to Particle 2: ";
    force.print();
    std::cout << " N\n";

    return 0;
}
