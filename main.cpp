#include <iostream>

int main() {
  const int IMAGE_HEIGHT = 256;
  const int IMAGE_WIDTH = 256;

  std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

  for (int j = 0; j < IMAGE_HEIGHT; j++) {
    std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' '
              << std::flush;

    for (int i = 0; i < IMAGE_WIDTH; i++) {
      auto r = double(i) / (IMAGE_WIDTH - 1);
      auto g = double(j) / (IMAGE_HEIGHT - 1);
      auto b = 0.0;

      int ir = int(255.999 * r);
      int ig = int(255.999 * g);
      int ib = int(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  std::clog << "\rDone.                 \n";
  return 0;
}