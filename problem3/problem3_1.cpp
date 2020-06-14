#include <iostream>
#include <fstream>
#include <cmath>

double const dx = 0.001;
double const dy = dx * 0.01;

// z ~ x + i * y

double f(double x, double y) {
  // | 1 + z + z^2/2 | - 1
  // = | 1 + a + (a^2 - b^2) / 2 + i(b + ab) | - 1
  // = sqrt((1 + a + (a^2 - b^2) / 2)^2 + (b + ab)^2) - 1
  double const re = 1 + x + (x * x - y * y) / 2;
  double const im = y + x * y;
  double const norm = std::sqrt(re * re + im * im);
  return norm - 1;
}

double solve(double x, double lb, double ub) {
  if(std::abs(lb - ub) < dy) return lb;

  double const mid = (lb + ub) / 2;
  double const midf = f(x, mid);
  if(midf < 0) return solve(x, mid, ub);
  return solve(x, lb, mid);
}

int main(int, char**) {
  std::ofstream os("RK2.dat");
  // `| 1 + z + z^2/2 | <= 1` は `Im(z) == 0` の時 [-2, 0] の範囲で成立、
  for(double x{-2 - dx}; x < (0 + dx); x += dx) {
    if(f(x, 0) >= 0) continue; // 符号が変わるところからはじめる。
    double y = 1;
    while(f(x, y) < 0) y *= 2; // 符号が変わってることろまでyを飛ばす。
    double const ans = solve(x, 0, y);
    os << x << ' ' << ans << std::endl;
  }
}
