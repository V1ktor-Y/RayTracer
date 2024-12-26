#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

bool hit_sphere(const point3 &center, double radius, const ray &r) {
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return (discriminant >= 0);
}

// Lerp => blendedValue=(1−a)*startValue+a*endValue
color ray_color(const ray &r) {
  if (hit_sphere(point3(0, 0, -1), 0.3, r))
    return color(0.75, 0, 0.35);

  vec3 normalized = normalized_vector(r.direction());
  auto a = 0.5 * (normalized.y() + 1);
  return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1);
}

int main() {
  // Set aspect ratio and calculate height
  const float ASPECT_RATIO = 16.0 / 9.0;
  int image_width = 512;
  int image_height = int(image_width / ASPECT_RATIO);
  image_height = image_height < 1 ? 1 : image_height;

  // Camera
  // Distance from camera to the viewport in the Z axis
  double focal_length = 1.0;
  double viewport_heigth = 2.0;
  double viewport_width =
      viewport_heigth * (double(image_width) / image_height);
  point3 camera_center = point3(0, 0, 0);

  // Horizontal vector for viewport
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  // Vertical vector for viewport
  // negative viewport_height since in space +y is up but in the image +y is
  // down (columns of pixels)
  vec3 viewport_v = vec3(0, -viewport_heigth, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;

  vec3 pixel00_location =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;

    for (int i = 0; i < image_width; i++) {
      // Find center of current pixel
      vec3 pixel_center =
          pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = pixel_center - camera_center;

      // Ray from camera towards center of pixel
      ray r(camera_center, ray_direction);
      color pixel_color = ray_color(r);

      writeColor(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";

  return 0;
}