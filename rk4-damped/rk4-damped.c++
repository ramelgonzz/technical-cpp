#include <iostream>
#include <fstream>
#include <iomanip>

// Struct for the state of the system
struct State {
    double x;  // position
    double v;  // velocity
};

// Parameters of the oscillator
const double m = 1.0;   // mass
const double c = 0.5;   // damping coefficient
const double k = 2.0;   // spring constant

// Time step
const double dt = 0.01;

// Compute derivatives
State derivative(const State& s) {
    State ds;
    ds.x = s.v;
    ds.v = -(c / m) * s.v - (k / m) * s.x;
    return ds;
}

// Runge-Kutta 4th order step
State rk4Step(const State& s, double t) {
    State k1 = derivative(s);

    State s2 = { s.x + 0.5 * dt * k1.x, s.v + 0.5 * dt * k1.v };
    State k2 = derivative(s2);

    State s3 = { s.x + 0.5 * dt * k2.x, s.v + 0.5 * dt * k2.v };
    State k3 = derivative(s3);

    State s4 = { s.x + dt * k3.x, s.v + dt * k3.v };
    State k4 = derivative(s4);

    State next;
    next.x = s.x + (dt / 6.0) * (k1.x + 2*k2.x + 2*k3.x + k4.x);
    next.v = s.v + (dt / 6.0) * (k1.v + 2*k2.v + 2*k3.v + k4.v);
    return next;
}

int main() {
    double t = 0.0;
    double t_max = 10.0;
    State s = { 1.0, 0.0 }; // Initial condition: x=1, v=0

    std::ofstream file("rk4_damped_oscillator.txt");
    file << "# time\tposition\tvelocity\n";
    file << std::fixed << std::setprecision(5);

    while (t <= t_max) {
        file << t << "\t" << s.x << "\t" << s.v << "\n";
        s = rk4Step(s, t);
        t += dt;
    }

    file.close();
    std::cout << "Simulation complete. Data saved to rk4_damped_oscillator.txt\n";
    return 0;
}
