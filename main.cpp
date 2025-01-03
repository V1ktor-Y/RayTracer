#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

double hit_sphere(const point3 &center, double radius, const ray &r) {
  vec3 oc = center - r.origin();

  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = h * h - a * c;

  return discriminant < 0 ? -1.0 : (h - std::sqrt(discriminant)) / a;
}

color ray_color(const ray &r) {
  auto t = hit_sphere(point3(0, 0, -1), 0.3, r);
  if (t > 0) {
    vec3 N = normalized_vector(r.at(t) - vec3(0, 0, -1));
    return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
  }
  // Lerp => blendedValue=(1−a)*startValue+a*endValue
  vec3 normalized = normalized_vector(r.direction());
  // change the range from (-1:1) to (0,1)
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