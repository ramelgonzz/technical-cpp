#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

const int N = 120;             // Number of points
const int HEIGHT = 30;         // Visual height
const int STEPS = 600;         // Time steps
const double c = 0.2;          // Wave speed factor
const int FRAME_DELAY_MS = 50; // Delay between frames

// Use Unicode blocks for visual effect
const char* BLOCK = "█";
const char* BASELINE = "─";

// Optional color (ANSI escape codes)
const std::string COLOR_CYAN = "\033[36m";
const std::string COLOR_RESET = "\033[0m";

// Clear terminal using ANSI escape codes
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// Clamp for C++14 and earlier
template <typename T>
T clamp(T value, T low, T high) {
    return std::max(low, std::min(value, high));
}

// Draw the wave using Unicode characters
void drawWave(const std::vector<double>& u) {
    std::vector<std::string> screen(HEIGHT, std::string(N, ' '));

    int mid = HEIGHT / 2;

    // Draw baseline
    for (int i = 0; i < N; ++i)
        screen[mid][i] = BASELINE[0];

    // Draw wave
    for (int i = 0; i < N; ++i) {
        int y = static_cast<int>((u[i]) * HEIGHT / 2.5) + mid;
        y = clamp(y, 0, HEIGHT - 1);
        screen[y][i] = BLOCK[0];
    }

    // Output screen buffer
    for (const auto& row : screen)
        std::cout << COLOR_CYAN << row << COLOR_RESET << "\n";
}

int main() {
    std::vector<double> u_prev(N, 0.0);
    std::vector<double> u(N, 0.0);
    std::vector<double> u_next(N, 0.0);

    // Initial pulse in the center
    u[N / 2] = 1.0;

    for (int t = 0; t < STEPS; ++t) {
        // Simulation step
        for (int i = 1; i < N - 1; ++i) {
            u_next[i] = 2 * u[i] - u_prev[i] + c * c * (u[i + 1] - 2 * u[i] + u[i - 1]);
        }

        u_prev = u;
        u = u_next;

        clearScreen();
        std::cout << "Time step: " << t << "\n";
        drawWave(u);

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
    }

    return 0;
}
