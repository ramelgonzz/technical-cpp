#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

struct OscillatorState {
    double time;
    double position;
    double velocity;
};

void exportToFile(const std::vector<OscillatorState>& data, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    outFile << "# Time(s)\tPosition(m)\tVelocity(m/s)\n";
    for (const auto& entry : data) {
        outFile << std::fixed << std::setprecision(5)
                << entry.time << "\t"
                << entry.position << "\t"
                << entry.velocity << "\n";
    }

    outFile.close();
    std::cout << "Data exported to: " << filename << "\n";
}

int main() {
    // Physical parameters
    double mass = 1.0;       // kg
    double k = 10.0;         // N/m
    double A = 1.0;          // amplitude (m)
    double omega = std::sqrt(k / mass);

    // Simulation parameters
    double dt = 0.01;        // time step
    double totalTime = 5.0;  // total time
    int steps = static_cast<int>(totalTime / dt);

    std::vector<OscillatorState> data;

    // Generate data
    for (int i = 0; i <= steps; ++i) {
        double t = i * dt;
        double x = A * std::cos(omega * t);
        double v = -A * omega * std::sin(omega * t);
        data.push_back({t, x, v});
    }

    // Export to file
    exportToFile(data, "harmonic_oscillator.txt");

    return 0;
}
