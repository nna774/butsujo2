#include <fstream>
#include <array>
#include <cmath>

int main(int, char**) {
  std::array<int, 5> const num{ 10, 100, 1000, 10000, 100000 };
  std::ofstream fp{"error.txt"};

  for(int i{}; i < num.size(); ++i) {
    double const delta{1.0 / num[i]};
    double y{1.0};

    for(int j{}; j < num[i]; ++j) {
      auto const ynew = y + delta * std::exp(-y);
      y = ynew;
    }

    float const error{static_cast<float>(y - std::log(1.0 + std::exp(1.0)))};
    fp << static_cast<float>(delta) << " " << error << " " << static_cast<float>(error / delta) << std::endl;
  }

  return 0;
}
