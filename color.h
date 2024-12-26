#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
#include <ostream>

using color = vec3;

void writeColor(std::ostream &out, const color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  int rbyte = int(255.99 * r);
  int gbyte = int(255.99 * g);
  int bbyte = int(255.99 * b);

  out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif