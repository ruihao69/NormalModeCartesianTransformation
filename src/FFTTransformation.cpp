#include "FFTTransformation.h"

FFTTransformation::FFTTransformation(int nbeads)
    : x_r(ComplexVector_t::Zero(nbeads)),
      x_k(ComplexVector_t::Zero(nbeads)),
      sqrt_2(std::sqrt(2)),
      N(nbeads),
      sqrt_N(std::sqrt(nbeads)){
  
  fft_forward = fftw_plan_dft_1d(nbeads, reinterpret_cast<fftw_complex*>(x_r.data()),
                       reinterpret_cast<fftw_complex*>(x_k.data()),
                       FFTW_FORWARD, FFTW_ESTIMATE);
  fft_inverse = fftw_plan_dft_1d(nbeads, reinterpret_cast<fftw_complex*>(x_k.data()),
                       reinterpret_cast<fftw_complex*>(x_r.data()),
                       FFTW_BACKWARD, FFTW_ESTIMATE);
  if (nbeads % 2 == 0) {
    copy_complex2real = &FFTTransformation::copy_complex2real_even;
    copy_real2complex = &FFTTransformation::copy_real2complex_even;
  } else{
    copy_complex2real = &FFTTransformation::copy_complex2real_odd;
    copy_real2complex = &FFTTransformation::copy_real2complex_odd;
  }
  half_N = (nbeads % 2 == 0) ? nbeads / 2 : nbeads / 2 + 1;
}

FFTTransformation::~FFTTransformation() {
  fftw_destroy_plan(fft_forward);
  fftw_destroy_plan(fft_inverse);
}



void FFTTransformation::transform_cartesian2normal(RealVector_t& v) const{
  x_r.real() = v;
  fftw_execute(fft_forward);
  copy_complex2real(this, v);
}

void FFTTransformation::transform_normal2cartesian(RealVector_t& v) const{
  copy_real2complex(this, v);
  fftw_execute(fft_inverse);
  // ldiv();
  v = x_r.real();
}

// Odd implementation
void FFTTransformation::copy_complex2real_odd(
    RealVector_t& v_real) const {
  x_k /= sqrt_N;
  v_real(0) = x_k(0).real();
  for (int ii = 1; ii < half_N; ii++) {
    v_real(ii) = x_k(ii).real() * sqrt_2;
    v_real(N - ii) = x_k(ii).imag() * sqrt_2;
  }
}

// Even implementation
void FFTTransformation::copy_complex2real_even(
    RealVector_t& v_real) const {
  x_k /= sqrt_N;
  v_real(0) = x_k(0).real();
  for (int ii = 1; ii < half_N; ii++) {
    v_real(ii) = x_k(ii).real() * sqrt_2;
    v_real(N - ii) = -x_k(ii).imag() * sqrt_2;
  }
  v_real(half_N) = x_k(half_N).real();
}

// Odd Implimentation
void FFTTransformation::copy_real2complex_odd(
    RealVector_t& v_real) const {
  for (int ii = 1; ii < half_N; ii++) {
    std::complex<double> tmp_cache {v_real(ii)/sqrt_2, v_real(N - ii)/sqrt_2};
    x_k(ii) = tmp_cache;
    x_k(N - ii) = conj(tmp_cache);
  }
  x_k(0) = std::complex<double>(v_real(0), 0.);
  x_k /= sqrt_N;
}

// Even Implimentation
void FFTTransformation::copy_real2complex_even(
    RealVector_t& v_real) const {
  for (int ii = 1; ii < half_N; ii++) {
    std::complex<double> tmp_cache {v_real(ii)/sqrt_2, v_real(N - ii)/sqrt_2};
    x_k(ii) = tmp_cache;
    x_k(N - ii) = conj(tmp_cache);
  }
  x_k(0) = std::complex<double>(v_real(0), 0.);
  x_k(half_N) = std::complex<double>(v_real(half_N), 0.);
  x_k /= sqrt_N;
}

// void FFTTransformation::ldiv() const { x_r = lu_solver.solve(x_r); }
