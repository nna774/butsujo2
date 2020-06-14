#include <iostream>
#include <fstream>
#include <array>
#include <cmath>

double const constexpr pi = std::atan(1.0) * 4;

double f2(double x, double y) {
  // | 1 + z + z^2/2 | - 1
  // = | 1 + a + (a^2 - b^2) / 2 + i(b + ab) | - 1
  // = sqrt((1 + a + (a^2 - b^2) / 2)^2 + (b + ab)^2) - 1
  double const re = 1 + x + (x * x - y * y) / 2;
  double const im = y + x * y;
  double const norm = std::sqrt(re * re + im * im);
  return norm - 1;
}
double f4(double x, double y) {
  std::array<double, 4> res, ims;
  res[0] = x;
  ims[0] = y;
  res[1] = x * res[0] - y * ims[0];
  ims[1] = x * ims[0] + y * res[0];
  res[2] = x * res[1] - y * ims[1];
  ims[2] = x * ims[1] + y * res[1];
  res[3] = x * res[2] - y * ims[2];
  ims[3] = x * ims[2] + y * res[2];
  double const sumr = 1 + res[0] + res[1] / 2 + res[2] / 6 + res[3] / 24;
  double const sumi = 0 + ims[0] + ims[1] / 2 + ims[2] / 6 + ims[3] / 24;
  return std::sqrt(sumr * sumr + sumi * sumi) - 1;
}

double const dr = 0.001;
double const dth = 2 * pi / 360;
int const inf = 1000000;

int main(int, char**) {
  {
    std::ofstream os("RK2_polar.dat");
    for(int i{}; i < 360; ++i) {
      for(int j{}; j < inf; ++j) {
        // (-0.5, 0)中心
        double x = -0.5 + std::cos(dth * i) * dr * j;
        double y = 0    + std::sin(dth * i) * dr * j;
        if(f2(x, y) >= 0) {
          os << x << ' ' << y << std::endl;
          break;
        }
      }
    }
  }
  {
    std::ofstream os("RK4.dat");
    for(int i{}; i < 360; ++i) {
      for(int j{}; j < inf; ++j) {
        // (-0.5, 0)中心
        double x = -0.5 + std::cos(dth * i) * dr * j;
        double y = 0    + std::sin(dth * i) * dr * j;
        if(f4(x, y) >= 0) {
          os << x << ' ' << y << std::endl;
          break;
        }
      }
    }
  }
}
