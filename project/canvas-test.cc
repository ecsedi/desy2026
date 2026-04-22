// compile: c++ -Wall -o canvas-test canvas-test.cc
// execute: ./canvas-test > test.ppm
// view test.ppm

#include "canvas.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char ** argv) {

  std::string outfilename = "-";

  if (argc > 1) {
    outfilename = argv[1];
  }

  Canvas canvas(255,255,RGB::white);
  for (int x = 0; x < 255; ++x) {
    for (int y = 0; y < 255; ++y) {
      canvas(x,y) = RGB(x, y, 0);
    }
  }

  canvas.save(outfilename);

  /*
  if (outfilename == "-") {
    std::cout << canvas << std::endl;
  }
  else {
    std::ofstream outfile(outfilename);
    outfile << canvas << std::endl;
    outfile.close();
  }
  */

  return 0;
}
