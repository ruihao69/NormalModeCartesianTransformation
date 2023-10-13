#include <chrono>
#include <iostream>
#include <random>

#include "RingPolymerData.h"

bool is_consistency(int nbeads) {
  RealVector_t p = RealVector_t::Random(nbeads);
  RealVector_t q = RealVector_t::Random(nbeads);

  auto u_fft = RingPolymerData(nbeads, p, q, true);
  auto u_explicit = RingPolymerData(nbeads, p, q, false);

  bool ret = true;

  u_explicit.transform_cartesian2normal();
  u_fft.transform_cartesian2normal();
  ret &= (u_fft == u_explicit);

  u_explicit.transform_normal2cartesian();
  u_fft.transform_normal2cartesian();
  ret &= (u_fft == u_explicit);

  return ret;
}

void consistency(int nbeads, int ntests) {
  int count_yes = 0;
  int count_no = 0;

  for (auto ii = 0; ii < ntests; ++ii) {
    if (is_consistency(nbeads)) {
      count_yes += 1;
    } else {
      count_no += 1;
    }
  }
  std::cout << "nbeads = " << nbeads << ". Testing consistency." << std::endl;
  std::cout << "For Normal Mode to Cartesian: " << std::endl;
  std::cout << "Within " << ntests << " randomized tests, " << count_yes
            << " tests are within tolerence. " << count_no
            << " exceed the tolerence." << std::endl;
  std::cout << std::endl;
}

int main() {
  const int nbeads_even = 100;
  const int nbeads_odd = 99;
  // const int nbeads_odd = 101; // large prime factor, slower fft
  const int ntests = 100000;

  consistency(nbeads_even, ntests);
  consistency(nbeads_odd, ntests);
}