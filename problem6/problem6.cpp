#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

int main(int, char**) {
  std::ofstream os("orbit.dat");
  std::ofstream mins("mindist.dat");
  double const dt = 0.00005;
  std::array<double, 4> const vs = {0.01, 0.1, 0.3, 0.5};
  int const step_by = 8;
  int const max_step = 40000;

  for(int i{}; i < vs.size(); ++i) {
    double x{1}, y{}, z{}, u{-1}, v{vs[i]}, w{};
    auto d = [&](){ return std::sqrt(x * x + y * y + z * z); };
    double dmin = d();

    for(int i{}; i < max_step; ++i) {
      // symplectic
      x += dt * u;
      y += dt * v;
      z += dt * w;
      double const r3 = std::pow(d(), 3);
      double const unew = u + dt * (v*z - w*y)/r3;
      double const vnew = v + dt * (w*x - u*z)/r3;
      double const wnew = w + dt * (u*y - v*x)/r3;
      u = unew;
      v = vnew;
      w = wnew;

      if(i / step_by * step_by == i) {
        os << x << ' ' << y << ' ' << z << ' ' << u << ' ' << v << ' ' << w << std::endl;
      }

      if(std::abs(x) > 5 || std::abs(y) > 5 || std::abs(z) > 5) break;
      dmin = std::min(d(), dmin);
    }

    mins << vs[i] << ' ' << dmin << std::endl;
    os << std::endl << std::endl;
  }
}
