#include <iostream>
#include <fstream>
#include <gsl/gsl_sf_bessel.h>

/*
Compile with:
g++ bessel.c++ -o bessel -lgsl -lgslcblas -lm
Run it, then plot the resulting txt data file:
gnuplot -e "plot 'bessel_data.txt' using 1:2 with lines title 'J_0(x)'; pause -1"
*/

int main() {
    const double x_min = 0.0;
    const double x_max = 20.0;
    const double step = 0.1;

    std::ofstream out("bessel_data.txt");
    if (!out) {
        std::cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    for (double x = x_min; x <= x_max; x += step) {
        double j0 = gsl_sf_bessel_J0(x); // Bessel function of the first kind, order 0
        out << x << "\t" << j0 << "\n";
    }

    out.close();
    std::cout << "Bessel function data written to bessel_data.txt\n";

    return 0;
}
