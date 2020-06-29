#include <iostream>
#include <fstream>
#include <cmath>

int main(int, char**) {
  {
    std::ofstream os("non.dat");
    for(int k{}; k < 4; ++k) { // 時間刻み
      int const n = 500 * std::pow(10, k);
      double const dt = 3.0 / n;
      int const ngraph = 5 * std::pow(10, std::max(0, k - 1));
      for(int i{}; i < 20; ++i) {
        double x = -10;
        double y = 0.1 - 0.2 * i / 19;
        double vx = 10;
        double vy = 0;

        for(int j{}; j < n; ++j) {
          // symplectic
          x += dt * vx;
          y += dt * vy;
          double const r3 = std::pow(std::sqrt(x * x + y * y), 3);
          vx += dt * x / r3;
          vy += dt * y / r3;

          if(j / ngraph * ngraph == j) {
            os << x << ' ' << y << ' ' << vx << ' ' << vy << std::endl;
          }
        }
      }
      os << std::endl << std::endl;
    }
  }

  {
    std::ofstream os("rela.dat");
    double const c = 12;
    double const c2 = c * c;

    for(int k{}; k < 4; ++k) {
      int const n = 500 * std::pow(10, k);
      double const dt = 3.0 / n;
      int const ngraph = 5 * std::pow(10, std::max(0, k - 1));
      for(int i{}; i < 20; ++i) {
        double x = -10;
        double y = 0.1 - 0.2 * i / 19;
        double vx = 10;
        double vy = 0;

        double v2 = std::pow(vx, 2) + std::pow(vy, 2);
        double px = vx / sqrt(1 - v2/c2);
        double py = vy / sqrt(1 - v2/c2);

        for(int j{}; j < n; ++j) {
          // symplectic
          double const p2 = px * px + py * py;
          x += dt * px / std::sqrt(p2/c2+1); 
          y += dt * py / std::sqrt(p2/c2+1);
          double const r3 = std::pow(std::sqrt(x * x + y * y), 3);
          px += dt * x / r3;
          py += dt * y / r3;

          if(j / ngraph * ngraph == j) {
            os << x << ' ' << y << ' ' << vx << ' ' << vy << std::endl;
          }
        }
      }
      os << std::endl << std::endl;
    }
  }
  return 0;
}
