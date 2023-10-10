#ifndef EXPLICIT_TRANSFORMATION_H
#define EXPLICIT_TRANSFORMATION_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include "NormalModeCartesianTransformation.h"

class ExplicitTransformation : public NormalModeCartesianTransformation {
 public:
  ExplicitTransformation(int /* nbeads */);
  ~ExplicitTransformation() = default;

  void transform_cartesian2normal(RealVector_t& /* v */) const override;
  void transform_normal2cartesian(RealVector_t& /* v */) const override;
  
 private:
  RealMatrix_t U;
  mutable RealVector_t v_tmp;
};

// void transform(RealVector_t& /* v */, const RealMatrix_t& /* U */, RealVector_t& /* v_tmp */);
RealMatrix_t get_Normal2CartFFT(int /* nbeads */);

#endif  // EXPLICIT_TRANSFORMATION_H
