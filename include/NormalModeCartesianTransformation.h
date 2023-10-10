#ifndef NORMAL_MODE_CARTESIAN_TRANSFORMATION_H 
#define NORMAL_MODE_CARTESIAN_TRANSFORMATION_H 

#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif

#include <fftw3.h>

#include <Eigen/Dense>
#include <complex>
#include <functional>

using ComplexMatrix_t = Eigen::MatrixXcd;
using ComplexVector_t = Eigen::VectorXcd;

using RealMatrix_t = Eigen::MatrixXd;
using RealVector_t = Eigen::VectorXd;

class NormalModeCartesianTransformation {

public:
    virtual void transform_cartesian2normal(RealVector_t& /* v */) const = 0;
    virtual void transform_normal2cartesian(RealVector_t& /* v */) const = 0;
    virtual ~NormalModeCartesianTransformation() = default;
};


#endif // NORMAL_MODE_CARTESIAN_TRANSFORMATION_H
