#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

double const constexpr a = 1;

int main(int, char**) {
  std::ofstream os("orbit.dat");
  double const dt = 0.00005;
  int const step_by = 100;
  int const max_step = 4000000;
  std::array<double, 5> bs{0.3, 1.9, 2, 2.1, 2.5};

  for(int i{}; i < bs.size(); ++i) {
    double const b = bs[i];

    double x{1}, y{0};
    auto f1 = [=](double x, double y) { return a - (b + 1) * x + x * x * y; };
    auto f2 = [=](double x, double y) { return b * x - x * x * y; };
    double dx{f1(x, y)}, 
           dy{f2(x, y)};

    for(int i{}; i < max_step; ++i) {
      // symplectic
      x += dt * dx;
      y += dt * dy;
      dx = f1(x, y);
      dy = f2(x, y);

      if(i / step_by * step_by == i) {
        os << x << ' ' << y << ' ' << dx << ' ' << dy << std::endl;
      }
    }

    os << std::endl << std::endl;
  }
}
