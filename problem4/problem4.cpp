#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

double const constexpr pi = std::atan(1.0) * 4;

int main(int, char**) {
  std::array<std::pair<double, char const*>, 4> const ps = {
    std::make_pair(.0, "eps0.dat"),
    std::make_pair(0.1, "eps01.dat"),
    std::make_pair(0.01, "eps001.dat"),
    std::make_pair(0.001, "eps0001.dat"),
  };
  double const dt = 0.0001;
  double const to = 4 * pi;
  int const max_step = to / dt + 1;
  int const points = 5000;
  int const write_by = to / points / dt;
  auto need_write = [write_by](int i) { return i / write_by * write_by == i; };
  for(auto e: ps) {
    double eps = e.first;
    std::ofstream os(e.second);
    double u = 1;
    double du = 0;
    for(int i{}; i < max_step; ++i) {
      // symplectic
      u += dt * du;
      du += dt * (-u + 2 + eps * std::pow(u, 2));
      if(need_write(i)) {
        double const t = dt * i;
        os << t << ' ' << u << std::endl;
      }
    }
  }
}
