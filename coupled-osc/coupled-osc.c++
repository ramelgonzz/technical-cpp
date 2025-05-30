#include <iostream>
#include <vector>
#include <iomanip>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Inline dot product of two vectors
inline double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    const size_t n = a.size();
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i] * b[i];
    return sum;
}

// Optimized matrix-vector multiplication
Vector multiply(const Matrix& A, const Vector& x) {
    const size_t rows = A.size();
    const size_t cols = x.size();
    Vector result(rows, 0.0);

    for (size_t i = 0; i < rows; ++i) {
        const std::vector<double>& row = A[i];
        result[i] = dotProduct(row, x);
    }

    return result;
}

// Optimized matrix-matrix multiplication
Matrix multiply(const Matrix& A, const Matrix& B) {
    const size_t rows = A.size();
    const size_t inner = A[0].size();
    const size_t cols = B[0].size();

    Matrix result(rows, std::vector<double>(cols, 0.0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t k = 0; k < inner; ++k) {
            const double a = A[i][k];
            for (size_t j = 0; j < cols; ++j) {
                result[i][j] += a * B[k][j];
            }
        }
    }

    return result;
}

// Pretty-print a vector
void printVector(const Vector& v) {
    for (double val : v)
        std::cout << std::setw(10) << val << " ";
    std::cout << "\n";
}

// Pretty-print a matrix
void printMatrix(const Matrix& M) {
    for (const auto& row : M)
        printVector(row);
    std::cout << "\n";
}

int main() {
    // Example system: Ax = b
    // A could represent coupling between 3 oscillators:
    Matrix A = {
        {2.0, -1.0, 0.0},
        {-1.0, 2.0, -1.0},
        {0.0, -1.0, 2.0}
    };

    // Right-hand side (external force or displacements)
    Vector b = {1.0, 0.0, 1.0};

    // Trial solution x0 (initial guess)
    Vector x = {0.0, 0.0, 0.0};

    // Simple Jacobi Iteration to solve Ax = b
    Vector x_new(3);
    const double tolerance = 1e-6;
    const int max_iter = 1000;
    int iter = 0;

    while (iter++ < max_iter) {
        for (size_t i = 0; i < 3; ++i) {
            double sum = b[i];
            for (size_t j = 0; j < 3; ++j) {
                if (j != i) sum -= A[i][j] * x[j];
            }
            x_new[i] = sum / A[i][i];
        }

        double err = 0.0;
        for (size_t i = 0; i < 3; ++i)
            err += std::abs(x_new[i] - x[i]);

        if (err < tolerance) break;
        x = x_new;
    }

    std::cout << "Solution to Ax = b:\n";
    printVector(x);

    return 0;
}
