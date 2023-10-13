#include <iostream>

#include "RingPolymerData.h"

int main() {
  std::cout << "Hello World!" << std::endl;
  const int nbeads = 100;
  RealVector_t p = RealVector_t::Random(nbeads);
  RealVector_t q = RealVector_t::Random(nbeads);

  auto u = RingPolymerData(nbeads, p, q);

  u.transform_cartesian2normal();
}