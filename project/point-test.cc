#include "point.h"
#include "position.h"
#include "boundingbox.h"
#include "transformation.h"
#include "canvas.h"
#include <iostream>
#include <random>
#include <vector>

int main() {

  Canvas             canvas(800, 600, RGB::white);
  BoundingBox        bbox;
  std::vector<Point> points;
  std::mt19937       rng(std::random_device{}());
  std::uniform_real_distribution<double> d(0, 1000);

  for (int i = 0; i < 300; ++i) {
    double x = d(rng);
    double y = d(rng);
    Point p({x,y}, RGB::red);
    points.push_back(p);
    bbox += p.boundingBox();
  }

  Transformation toScreen = Transformation::toScreen(bbox, canvas.width(), canvas.height());

  for (auto & p : points) {
    canvas << toScreen*p;
  }

  std::cout << canvas;
  return 0;
}
