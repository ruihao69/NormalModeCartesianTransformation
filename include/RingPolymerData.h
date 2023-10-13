#ifndef RING_POLYMER_DATA_H
#define RING_POLYMER_DATA_H

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include <memory>

#include "NormalModeCartesianTransformation.h"

struct RingPolymerData {
  RealVector_t q;
  RealVector_t p;
  std::unique_ptr<NormalModeCartesianTransformation> transform;

  RingPolymerData(int /* nbeads */, const RealVector_t& /* p */,
                  const RealVector_t& /* q */);

  RingPolymerData(int /* nbeads */, const RealVector_t& /* p */,
                  const RealVector_t& /* q */, bool use_FFT);

  bool operator==(const RingPolymerData& /* other */) const;

  void transform_cartesian2normal();
  void transform_normal2cartesian();

  void q_transform_cartesian2normal();
  void q_transform_normal2cartesian();
  void p_transform_cartesian2normal();
  void p_transform_normal2cartesian();
};

std::unique_ptr<NormalModeCartesianTransformation> get_transform(
    int /* nbeads */);
std::unique_ptr<NormalModeCartesianTransformation> get_transform(
    int /* nbeads */, bool /* use_FFT */);

#endif  // RING_POLYMER_DATA_H