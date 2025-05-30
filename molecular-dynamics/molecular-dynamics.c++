#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm> // for std::clamp

const double BOX_SIZE = 10.0;
const double PARTICLE_RADIUS = 0.1;
const double TIME_STEP = 0.005;
const int NUM_PARTICLES = 20;
const int NUM_STEPS = 10000;
const double MASS = 1.0;
const double BOLTZMANN = 1.380649e-23;

struct Vector2D {
    double x = 0, y = 0;

    Vector2D operator+(const Vector2D& b) const { return {x + b.x, y + b.y}; }
    Vector2D operator-(const Vector2D& b) const { return {x - b.x, y - b.y}; }
    Vector2D operator*(double s) const { return {x * s, y * s}; }
    double dot(const Vector2D& b) const { return x * b.x + y * b.y; }
    double norm2() const { return x * x + y * y; }
};

class Particle {
public:
    Vector2D pos, vel;

    Particle(Vector2D p, Vector2D v) : pos(p), vel(v) {}

    void move(double dt) {
        pos = pos + vel * dt;

        // Wall collisions (elastic)
        if (pos.x < PARTICLE_RADIUS || pos.x > BOX_SIZE - PARTICLE_RADIUS) vel.x *= -1;
        if (pos.y < PARTICLE_RADIUS || pos.y > BOX_SIZE - PARTICLE_RADIUS) vel.y *= -1;

        pos.x = std::clamp(pos.x, PARTICLE_RADIUS, BOX_SIZE - PARTICLE_RADIUS);
        pos.y = std::clamp(pos.y, PARTICLE_RADIUS, BOX_SIZE - PARTICLE_RADIUS);
    }

    double kineticEnergy() const {
        return 0.5 * MASS * vel.norm2();
    }
};

class Simulation {
    std::vector<Particle> particles;
    std::ofstream pos_out, energy_out;
    std::mt19937 rng;

public:
    Simulation() {
        rng.seed(42);
        std::uniform_real_distribution<double> dist(PARTICLE_RADIUS, BOX_SIZE - PARTICLE_RADIUS);
        std::normal_distribution<double> vdist(0.0, 1.0);

        for (int i = 0; i < NUM_PARTICLES; ++i) {
            Vector2D pos = {dist(rng), dist(rng)};
            Vector2D vel = {vdist(rng), vdist(rng)};
            particles.emplace_back(pos, vel);
        }

        pos_out.open("positions.txt");
        energy_out.open("energies.txt");
    }

    void run() {
        for (int step = 0; step < NUM_STEPS; ++step) {
            handleCollisions();
            double total_energy = 0;

            for (auto& p : particles) {
                p.move(TIME_STEP);
                total_energy += p.kineticEnergy();
            }

            double temperature = (2.0 / (2.0 * NUM_PARTICLES)) * total_energy / BOLTZMANN;

            if (step % 50 == 0) {
                logPositions(step * TIME_STEP);
                energy_out << step * TIME_STEP << "\t" << total_energy << "\t" << temperature << "\n";
            }
        }
    }

    void handleCollisions() {
        for (size_t i = 0; i < particles.size(); ++i) {
            for (size_t j = i + 1; j < particles.size(); ++j) {
                Vector2D dp = particles[j].pos - particles[i].pos;
                if (dp.norm2() < 4 * PARTICLE_RADIUS * PARTICLE_RADIUS) {
                    Vector2D dv = particles[j].vel - particles[i].vel;
                    double dp_dot_dv = dp.dot(dv);
                    if (dp_dot_dv < 0) {
                        Vector2D correction = dp * (dp_dot_dv / dp.norm2());
                        particles[i].vel = particles[i].vel + correction;
                        particles[j].vel = particles[j].vel - correction;
                    }
                }
            }
        }
    }

    void logPositions(double t) {
        for (const auto& p : particles)
            pos_out << t << "\t" << p.pos.x << "\t" << p.pos.y << "\n";
        pos_out << "\n";
    }

    ~Simulation() {
        pos_out.close();
        energy_out.close();
    }
};

int main() {
    Simulation sim;
    sim.run();
    std::cout << "Simulation complete. Data saved to positions.txt and energies.txt\n";
    return 0;
}
