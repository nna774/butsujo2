#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double const constexpr pi = std::atan(1.0) * 4;

int main(int, char**) {
  double const dt = 0.0001;
  double const to = 4 * pi;
  int const max_step = to / dt + 1;
  double start = 1.25;

  std::ofstream os("eps-T.dat");
  std::vector<double> epss;
  {
    int const N = 100;
    double const step = std::pow(0.1 / 0.001, 1.0/N);
    for(int i{}; i < N; ++i) {
      epss.push_back(0.001 * std::pow(step, i));
    }
  }
  for(double eps: epss) {
    double u = 1;
    double du = 0;
    int state = 0;
    int timer = 0;
    for(int i{}; i < max_step; ++i) {
      // symplectic
      u += dt * du;
      du += dt * (-u + 2 + eps * std::pow(u, 2));
      if(state == 0) {
        if(u > start) {
          state = 1;
          timer = i;
        }
      } else if(state == 1) {
        if(u < start) {
          state = 2;
        }
      } else if(state == 2) {
        if(u > start) {
          double const T = (i - timer) * dt;
          os << eps << ' ' << (T - 2 * pi) << std::endl;
          break;
        }
      }
    }
  }
}
