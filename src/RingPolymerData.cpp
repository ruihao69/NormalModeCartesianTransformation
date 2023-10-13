#include "RingPolymerData.h"

#include "ExplicitTransformation.h"
#include "FFTTransformation.h"

RingPolymerData::RingPolymerData(int nbeads, const RealVector_t& q,
                                 const RealVector_t& p)
    : q(q), p(p), transform(get_transform(nbeads)) {
  if (q.size() != p.size()) {
    throw std::invalid_argument(
        "position `q` and momentum `p` must have the same size.");
  }
  if (q.size() != nbeads) {
    throw std::invalid_argument(
        "The number of beads `nbeads` doesn't math the dimension of the "
        "position momentum");
  }
}

RingPolymerData::RingPolymerData(int nbeads, const RealVector_t& q,
                                 const RealVector_t& p, bool use_FFT)
    : q(q), p(p), transform(get_transform(nbeads, use_FFT)) {
  if (q.size() != p.size()) {
    throw std::invalid_argument(
        "position `q` and momentum `p` must have the same size.");
  }
  if (q.size() != nbeads) {
    throw std::invalid_argument(
        "The number of beads `nbeads` doesn't math the dimension of the "
        "position momentum");
  }
}

bool RingPolymerData::operator==(const RingPolymerData& other) const {
  double tolerance = 1e-12;  // Default tolerance

  for (auto i = 0; i < q.size(); ++i) {
    if (std::abs(q[i] - other.q[i]) > tolerance ||
        std::abs(p[i] - other.p[i]) > tolerance) {
      return false;  // Vectors are not very close
    }
  }

  return true;  // Vectors are very close within the specified tolerance
}

void RingPolymerData::transform_cartesian2normal() {
  transform->transform_cartesian2normal(p);
  transform->transform_cartesian2normal(q);
}

void RingPolymerData::transform_normal2cartesian() {
  transform->transform_normal2cartesian(p);
  transform->transform_normal2cartesian(q);
}

void RingPolymerData::p_transform_cartesian2normal() {
  transform->transform_cartesian2normal(p);
}

void RingPolymerData::q_transform_cartesian2normal() {
  transform->transform_cartesian2normal(q);
}

void RingPolymerData::p_transform_normal2cartesian() {
  transform->transform_normal2cartesian(p);
}

void RingPolymerData::q_transform_normal2cartesian() {
  transform->transform_normal2cartesian(q);
}

std::unique_ptr<NormalModeCartesianTransformation> get_transform(int nbeads) {
  if (nbeads > 40) {
    return std::make_unique<FFTTransformation>(nbeads);
  } else {
    return std::make_unique<ExplicitTransformation>(nbeads);
  }
}

std::unique_ptr<NormalModeCartesianTransformation> get_transform(int nbeads,
                                                                 bool use_FFT) {
  if (use_FFT) {
    return std::make_unique<FFTTransformation>(nbeads);
  } else {
    return std::make_unique<ExplicitTransformation>(nbeads);
  }
}
