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
  std::uniform_real_distribution<double> d1(0, 100);

  for (int i = 0; i < 2000; ++i) {
    double x = d1(rng);
    double y = d1(rng);
    Point p({x,y}, RGB::red);
    points.push_back(p);
    bbox += p.boundingBox();
  }

  std::uniform_real_distribution<double> d2(900, 1000);

  for (int i = 0; i < 2000; ++i) {
    double x = d2(rng);
    double y = d2(rng);
    Point p({x,y}, RGB::red);
    points.push_back(p);
    bbox += p.boundingBox();
  }

  bbox *= 1.05;
  Transformation toScreen = Transformation::toScreen(bbox, canvas.width(), canvas.height());

  for (auto & p : points) {
    canvas << toScreen*p;
  }

  std::cout << canvas;
  return 0;
}
