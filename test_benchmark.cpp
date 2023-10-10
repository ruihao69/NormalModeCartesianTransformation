#include <iostream>
#include <random>
#include <chrono>

#include "FFTTransformation.h"
#include "ExplicitTransformation.h"

void benchmark_transform(int ntests, const NormalModeCartesianTransformation& transform, RealVector_t& v)
{
  auto start = std::chrono::high_resolution_clock::now();
  for (int ii=0; ii<ntests; ++ii){
    transform.transform_cartesian2normal(v);
    transform.transform_normal2cartesian(v);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
}

int main(){
    std::cout << "Hello World!" << std::endl;

    const int nbeads = 100;
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    RealVector_t v = RealVector_t::Zero(nbeads);
    for (int ii=0; ii<nbeads; ++ii){
        v(ii) = dis(gen);
    }

    const int ntests = 10000000;

    FFTTransformation fft_transform {nbeads};
    std::cout  << "Testing FFT method: " << std::endl;
    benchmark_transform(ntests, fft_transform, v);

    ExplicitTransformation explicit_transform {nbeads};
    std::cout  << "Testing explicit method: " << std::endl;
    benchmark_transform(ntests, explicit_transform, v);

    return 0;
}
