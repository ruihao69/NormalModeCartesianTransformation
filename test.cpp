#include <iostream>
#include <random>
#include <chrono>

#include "FFTTransformation.h"
#include "ExplicitTransformation.h"

// Initialize random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0.0, 1.0);

void randmize(RealVector_t& v1, RealVector_t& v2){
    for (int ii=0; ii<v1.rows(); ++ii){
            v1(ii) = v2(ii) = dis(gen);
        }
}

int main(){
    std::cout << "Hello World!" << std::endl;

    const int nbeads = 11;
    const int ntests = 100000;

    FFTTransformation fft_transform {nbeads};
    ExplicitTransformation explicit_transform {nbeads};

    RealVector_t v1 = RealVector_t::Zero(nbeads);
    RealVector_t v2 = RealVector_t::Zero(nbeads);
    RealVector_t vtmp = RealVector_t::Zero(nbeads);

    randmize(v1, v2);
    std::cout << "These were vectors random drawned" << std::endl;
    std::cout<< v1.transpose() << std::endl;
    std::cout<< v2.transpose() << std::endl;

    fft_transform.transform_cartesian2normal(v1);
    explicit_transform.transform_cartesian2normal(v2);

    std::cout<< v1.transpose() << std::endl;
    std::cout<< v2.transpose() << std::endl;
}
