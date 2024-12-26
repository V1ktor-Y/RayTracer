#include "color.h"
#include "vec3.h"
#include <iostream>

int main() {
  const int IMAGE_HEIGHT = 256;
  const int IMAGE_WIDTH = 256;

  std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

  for (int j = 0; j < IMAGE_HEIGHT; j++) {
    std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' '
              << std::flush;

    for (int i = 0; i < IMAGE_WIDTH; i++) {
      auto pixelColor = color(double(i), double(j), 0);
      writeColor(std::cout, normalized_vector(pixelColor));
    }
  }
  std::clog << "\rDone.                 \n";
  return 0;
}