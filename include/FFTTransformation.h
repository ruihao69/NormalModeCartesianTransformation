#ifndef FFT_TRANSFORMATION_H
#define FFT_TRANSFORMATION_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include "NormalModeCartesianTransformation.h"

class FFTTransformation : public NormalModeCartesianTransformation {
 public:
  FFTTransformation(int /* nbeads */);
  ~FFTTransformation();

  void transform_cartesian2normal(RealVector_t& /* v */) const override;
  void transform_normal2cartesian(RealVector_t& /* v */) const override;

 private:
  std::function<void(const FFTTransformation*, RealVector_t&)> copy_complex2real;
  std::function<void(const FFTTransformation*, RealVector_t&)> copy_real2complex;

  // void copy_complex2real(RealVector_t& v_real) const;
  // void copy_real2complex(RealVector_t& v_real) const;

  
  void copy_complex2real_even(RealVector_t& v_real) const;
  void copy_real2complex_even(RealVector_t& v_real) const;
  void copy_complex2real_odd(RealVector_t& v_real) const;
  void copy_real2complex_odd(RealVector_t& v_real) const;

 private:
  fftw_plan fft_forward;
  fftw_plan fft_inverse;
  mutable ComplexVector_t x_r;
  mutable ComplexVector_t x_k;
  double sqrt_2;
  int N;
  int half_N;
  double sqrt_N;
};

#endif  // FFT_TRANSFORMATION_H
