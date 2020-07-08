#include <iostream>
#include <fstream>
#include <cmath>

int const N = 500;
int const NARRAY = N * 2 + 1;
double const xstart = -20;
double const xend = 0;
double const dx =  (xend - xstart) / N;

int main(int, char**) {
  {
    std::ofstream os("oddf.dat");
    double us[NARRAY], xs[NARRAY];
    double umax, uprev;
    double E;
    for(int j{}; j < 5000; ++j) {
      E = -0.093 + 0.000001 * j;
      auto F = [&E](double x) {
        return -3 * std::pow(1/std::cosh(x), 2) - E;
      };
      double x = xstart;
      double u = 1.0e-5;
      double p = u * std::sqrt(F(xstart));
      xs[0] = x;
      us[0] = u;
      umax = std::abs(u);
      for(int i{1}; i <= N; ++i) {
        double aus[4], aps[4];
        aus[0] = p;
        aps[0] = F(x) * u;
        aus[1] = p + aps[0] * dx / 2;
        aps[1] = F(x + dx/2) * (u + aus[0] * dx / 2);
        aus[2] = p + aps[1] * dx / 2;
        aps[2] = F(x + dx/2) * (u + aus[1] * dx / 2);
        aus[3] = p + aps[2] * dx;
        aps[3] = F(x + dx) * (u + aus[2] * dx);

        u += (aus[0] + aus[1] * 2 + aus[2] * 2 + aus[3]) * dx / 6;
        p += (aps[0] + aps[1] * 2 + aps[2] * 2 + aps[3]) * dx / 6;
        x += dx;
        /*
        u += p * dx;
        x += dx;
        p += F(x) * u * dx;
        */

        xs[i] = x;
        us[i] = u;
        umax = std::max(umax, std::abs(u));
      }

      if(j > 0) {
        if(uprev * u < 0) { 
          std::cout << "sign changed" << std::endl;
          break;
        }
      }
      uprev = u;
    }
    std::cout << "energy = " << E << std::endl;

    for(int i{N+1}; i < NARRAY; ++i) {
      xs[i] = -xs[2 * N - i];
      us[i] = -us[2 * N - i];
    }
    for(int i{}; i < NARRAY; ++i) us[i] = us[i] / umax;
    auto step_by = NARRAY / 200;
    for(int i{}; i < NARRAY; i+=step_by) {
      os << xs[i] << ' ' << us[i] << std::endl;
    }
  }
  std::cout << "even part" << std::endl;
  {
    std::ofstream os("evenf.dat");
    double us[NARRAY], xs[NARRAY];
    double umax, pprev;
    double E;
    for(int j{}; j < 5000; ++j) {
      E = -1.695 - 0.000001 * j;
      auto F = [&E](double x) {
        return -3 * std::pow(1/std::cosh(x), 2) - E;
      };
      double x = xstart;
      double u = 1.0e-5;
      double p = u * std::sqrt(F(xstart));
      xs[0] = x;
      us[0] = u;
      umax = std::abs(u);
      double pp;
      for(int i{1}; i <= N; ++i) {
        double aus[4], aps[4];
        aus[0] = p;
        aps[0] = F(x) * u;
        aus[1] = p + aps[0] * dx / 2;
        aps[1] = F(x + dx/2) * (u + aus[0] * dx / 2);
        aus[2] = p + aps[1] * dx / 2;
        aps[2] = F(x + dx/2) * (u + aus[1] * dx / 2);
        aus[3] = p + aps[2] * dx;
        aps[3] = F(x + dx) * (u + aus[2] * dx);

        u += (aus[0] + aus[1] * 2 + aus[2] * 2 + aus[3]) * dx / 6;
        p += (aps[0] + aps[1] * 2 + aps[2] * 2 + aps[3]) * dx / 6;
        x += dx;

        xs[i] = x;
        us[i] = u;
        umax = std::max(umax, std::abs(u));
      }

      if(j > 0) {
        if(pprev * p < 0) { 
          std::cout << "sign changed" << std::endl;
          break;
        }
      }
      pprev = p;
    }
    std::cout << "energy = " << E << std::endl;

    for(int i{N+1}; i < NARRAY; ++i) {
      xs[i] = -xs[2 * N - i];
      us[i] = us[2 * N - i];
    }
    for(int i{}; i < NARRAY; ++i) us[i] = us[i] / umax;
    auto step_by = NARRAY / 200;
    for(int i{}; i < NARRAY; i+=step_by) {
      os << xs[i] << ' ' << us[i] << std::endl;
    }
  }
}
