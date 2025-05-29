#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>  // for std::setw and std::setprecision

struct DataPoint {
    double time;
    double position;
};

void saveData(const std::vector<DataPoint>& data, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }

    outFile << "# Time(s)\tPosition(m)\n";
    for (const auto& point : data) {
        outFile << std::fixed << std::setprecision(4)
                << point.time << "\t" << point.position << "\n";
    }

    outFile.close();
    std::cout << "Data saved to " << filename << "\n";
}

std::vector<DataPoint> readData(const std::string& filename) {
    std::vector<DataPoint> data;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << "\n";
        return data;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Skip comments or empty lines
        if (line.empty() || line[0] == '#') continue;

        DataPoint dp;
        std::istringstream iss(line);
        if (iss >> dp.time >> dp.position) {
            data.push_back(dp);
        }
    }

    inFile.close();
    return data;
}

int main() {
    // Simulate motion: x(t) = v * t
    const double velocity = 2.5;  // m/s
    const double dt = 0.5;        // s
    const int steps = 10;

    std::vector<DataPoint> simulationData;
    for (int i = 0; i <= steps; ++i) {
        double t = i * dt;
        double x = velocity * t;
        simulationData.push_back({t, x});
    }

    const std::string filename = "simulation_data.txt";

    // Save to file
    saveData(simulationData, filename);

    // Read it back
    std::cout << "\nReading data from file:\n";
    auto readBackData = readData(filename);
    for (const auto& dp : readBackData) {
        std::cout << "Time: " << dp.time << " s, Position: " << dp.position << " m\n";
    }

    return 0;
}
