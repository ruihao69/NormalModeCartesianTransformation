#include <iostream>
#include <random>
#include <chrono>

#include "FFTTransformation.h"
#include "ExplicitTransformation.h"

// Initialize random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(-100.0, 100.0);

void randmize(RealVector_t& v1, RealVector_t& v2){
    for (int ii=0; ii<v1.rows(); ++ii){
            v1(ii) = v2(ii) = dis(gen);
        }
}

void consistency_check(int nbeads, int ntests, const FFTTransformation& fft_transform, const ExplicitTransformation& explicit_transform, double tol=1e-10)
{
    RealVector_t v1 = RealVector_t::Zero(nbeads);
    RealVector_t v2 = RealVector_t::Zero(nbeads);
    RealVector_t vtmp = RealVector_t::Zero(nbeads);
    int count_yes = 0;
    int count_no = 0;
    for (int ii=0; ii<ntests; ++ii){
        randmize(v1, v2);
        fft_transform.transform_cartesian2normal(v1);
        explicit_transform.transform_cartesian2normal(v2);
        vtmp = v2 - v1;
        double diff = vtmp.norm();
        (diff < tol) ? (count_yes += 1) : (count_no += 1);
    }
    std::cout << "For Cartesian to Normal Mode: " << std::endl;
    std::cout << "Within " << ntests << " randomized tests, " << count_yes << " tests are within tolerence. " << count_no << " exceed the tolerence." << std::endl;

    count_yes = count_no = 0;
    for (int ii=0; ii<ntests; ++ii){
        randmize(v1, v2);
        fft_transform.transform_normal2cartesian(v1);
        explicit_transform.transform_normal2cartesian(v2);
        vtmp = v2 - v1;
        double diff = vtmp.norm();
        (diff < tol) ? (count_yes += 1) : (count_no += 1);
    }
    std::cout << "For Normal Mode to Cartesian: " << std::endl;
    std::cout << "Within " << ntests << " randomized tests, " << count_yes << " tests are within tolerence. " << count_no << " exceed the tolerence." << std::endl;
}

int main(){
    std::cout << "Hello World!" << std::endl;
    std::cout << std::endl;

    const int nbeads_even = 200;
    const int nbeads_odd = 101;
    const int ntests = 100000;

    FFTTransformation fft_transform_even {nbeads_even};
    ExplicitTransformation explicit_transform_even {nbeads_even};

    std::cout << "Even beads consistence check:" << std::endl;
    consistency_check(nbeads_even, ntests, fft_transform_even, explicit_transform_even);
    std::cout << std::endl;


    FFTTransformation fft_transform_odd {nbeads_odd};
    ExplicitTransformation explicit_transform_odd {nbeads_odd};
    std::cout << "Odd beads consistence check:" << std::endl;
    consistency_check(nbeads_odd, ntests, fft_transform_odd, explicit_transform_odd);

    return 0;
}
