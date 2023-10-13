#include <chrono>
#include <iostream>
#include <random>

#include "RingPolymerData.h"

void benchmark_transform(int ntests, RingPolymerData& rpdata) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int ii = 0; ii < ntests; ++ii) {
    rpdata.transform_cartesian2normal();
    rpdata.transform_normal2cartesian();
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
}

void benchmark(int nbeads, int ntests) {
  RealVector_t p = RealVector_t::Random(nbeads);
  RealVector_t q = RealVector_t::Random(nbeads);

  auto u_fft = RingPolymerData(nbeads, p, q, true);
  auto u_explicit = RingPolymerData(nbeads, p, q, false);
  std::cout << "nbeads = " << nbeads << ". Testing FFT." << std::endl;
  benchmark_transform(ntests, u_fft);
  std::cout << std::endl;

  std::cout << "nbeads = " << nbeads << ". Testing explicit." << std::endl;
  benchmark_transform(ntests, u_explicit);
  std::cout << std::endl;
}

int main() {
  const int nbeads_even = 100;
  const int nbeads_odd = 99;
  // const int nbeads_odd = 101; // large prime factor, slower fft
  const int ntests = 10000000;

  benchmark(nbeads_even, ntests);
  benchmark(nbeads_odd, ntests);
}