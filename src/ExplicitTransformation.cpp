#include "ExplicitTransformation.h"

ExplicitTransformation::ExplicitTransformation(int nbeads)
     : U(get_Normal2CartFFT(nbeads)), v_tmp(RealVector_t::Zero(nbeads)) {}

void ExplicitTransformation::transform_cartesian2normal(RealVector_t& v) const {
    v_tmp.noalias() = U.transpose() * v;  // Efficiently compute U * v and store in v_tmp
    v = v_tmp;                // Copy v_tmp to v
 }

 void ExplicitTransformation::transform_normal2cartesian(RealVector_t& v) const {
    v_tmp.noalias() = U * v;  // Efficiently compute U * v and store in v_tmp
    v = v_tmp;                // Copy v_tmp to v
 }

RealMatrix_t get_Normal2CartFFT(int nbeads) {
  RealMatrix_t FFT = RealMatrix_t::Zero(nbeads, nbeads);
  for (int ii(0); ii < nbeads; ++ii) {
    for (int jj(0); jj < nbeads; ++jj) {
      if (jj == 0) {
        FFT(ii, jj) = 1.0 / std::sqrt(nbeads);
      } else if (jj < nbeads / 2.0) {
        FFT(ii, jj) =
            std::sqrt(2.0 / nbeads) * std::cos(2.0 * M_PI * ii * jj / nbeads);
      } else if ((jj == nbeads / 2) & ((nbeads + 1) % 2)) {
        FFT(ii, jj) = std::pow(-1.0, ii) / std::sqrt(nbeads);
      } else {
        FFT(ii, jj) =
            std::sqrt(2.0 / nbeads) * std::sin(2.0 * M_PI * ii * jj / nbeads);
      }
    }
  }
  return FFT;
}
