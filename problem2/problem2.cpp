#include <fstream>
#include <array>
#include <cmath>

double const dt{0.2};
double const to{20};
int const max_step{static_cast<int>(to/dt)};
auto const show = [](std::ofstream& fp, double x, double y, double u, double v) {
  fp << x << ' ' << y << ' ' << u << ' ' << v << std::endl;
};

void euler(std::ofstream& fp) {
  double x{1}, y{0}, u{0}, v{1};
  for(int i{}; i < max_step; ++i) {
    auto const r3 = std::pow(std::sqrt(std::pow(x, 2) + std::pow(y, 2)), 3);
    auto const newu = u - (x / r3) * dt;
    auto const newv = v - (y / r3) * dt;
    x += dt * u;
    y += dt * v;
    u = newu;
    v = newv;
    show(fp, x, y, u, v);
  }
}

void rk2(std::ofstream& fp) {
  double x{1}, y{0}, u{0}, v{1};
  for(int i{}; i < max_step; ++i) {
    auto const r3 = std::pow(std::sqrt(std::pow(x, 2) + std::pow(y, 2)), 3);
    auto const atx = u;
    auto const aty = v;
    auto const atu = - x / r3;
    auto const atv = - y / r3;
    auto const tx = x + atx * dt;
    auto const ty = y + aty * dt;
    auto const tu = u + atu * dt;
    auto const tv = v + atv * dt;

    auto const r32 = std::pow(std::sqrt(std::pow(tx, 2) + std::pow(ty, 2)), 3);
    auto const at2x = tu;
    auto const at2y = tv;
    auto const at2u = - tx / r32;
    auto const at2v = - ty / r32;

    x = x + dt * (atx + at2x) / 2;
    y = y + dt * (aty + at2y) / 2;
    u = u + dt * (atu + at2u) / 2;
    v = v + dt * (atv + at2v) / 2;
    show(fp, x, y, u, v);
  }
}

void rk4(std::ofstream& fp) {
  double x{1}, y{0}, u{0}, v{1};
  for(int i{}; i < max_step; ++i) {
    std::array<double, 4> r3s, atxs, atys, atus, atvs, txs, tys, tus, tvs;
    r3s[0] = std::pow(std::sqrt(std::pow(x, 2) + std::pow(y, 2)), 3);
    atxs[0] = u;
    atys[0] = v;
    atus[0] = - x / r3s[0];
    atvs[0] = - y / r3s[0];
    txs[0] = x + atxs[0] * dt / 2;
    tys[0] = y + atys[0] * dt / 2;;
    tus[0] = u + atus[0] * dt / 2;;
    tvs[0] = v + atvs[0] * dt / 2;;

    r3s[1] = std::pow(std::sqrt(std::pow(txs[0], 2) + std::pow(tys[0], 2)), 3);
    atxs[1] = tus[0];
    atys[1] = tvs[0];
    atus[1] = - txs[0] / r3s[1];
    atvs[1] = - tys[0] / r3s[1];
    txs[1] = x + atxs[1] * dt / 2;
    tys[1] = y + atys[1] * dt / 2;;
    tus[1] = u + atus[1] * dt / 2;;
    tvs[1] = v + atvs[1] * dt / 2;;

    r3s[2] = std::pow(std::sqrt(std::pow(txs[1], 2) + std::pow(tys[1], 2)), 3);
    atxs[2] = tus[1];
    atys[2] = tvs[1];
    atus[2] = - txs[1] / r3s[2];
    atvs[2] = - tys[1] / r3s[2];
    txs[2] = x + atxs[2] * dt;
    tys[2] = y + atys[2] * dt;
    tus[2] = u + atus[2] * dt;
    tvs[2] = v + atvs[2] * dt;

    r3s[3] = std::pow(std::sqrt(std::pow(txs[2], 2) + std::pow(tys[2], 2)), 3);
    atxs[3] = tus[2];
    atys[3] = tvs[2];
    atus[3] = - txs[2] / r3s[3];
    atvs[3] = - tys[2] / r3s[3];

    x += dt * (atxs[0] + 2 * atxs[1] + 2 * atxs[2] + atxs[3]) / 6;
    y += dt * (atys[0] + 2 * atys[1] + 2 * atys[2] + atys[3]) / 6;
    u += dt * (atus[0] + 2 * atus[1] + 2 * atus[2] + atus[3]) / 6;
    v += dt * (atvs[0] + 2 * atvs[1] + 2 * atvs[2] + atvs[3]) / 6;
    show(fp, x, y, u, v);
  }
}

void symplectic(std::ofstream& fp) {
  double x{1}, y{0}, u{0}, v{1};
  for(int i{}; i < max_step; ++i) {
    x += dt * u;
    y += dt * v;
    auto const r3 = std::pow(std::sqrt(std::pow(x, 2) + std::pow(y, 2)), 3);
    u += - (x / r3) * dt;
    v += - (y / r3) * dt;
    show(fp, x, y, u, v);
  }
}

int main(int, char**) {
  std::ofstream fp{"orbit.dat"};

  euler(fp);
  fp << std::endl << std::endl;
  rk2(fp);
  fp << std::endl << std::endl;
  rk4(fp);
  fp << std::endl << std::endl;
  symplectic(fp);

  return 0;
}
