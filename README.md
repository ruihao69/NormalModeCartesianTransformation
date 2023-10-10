# NormalModeCartesianTransformation

![Build Status](https://img.shields.io/github/actions/workflow/status/ruihao69/NormalModeCartesianTransformation/build.yml)

`c++` package for ring polymer coordinates transformation, between cartesian and normal mode coordinates.

The convention for the DFT matrix follows Eq.(18) in article "Efficient stochastic thermostatting of path integral molecular dynamics." [JCP2010](https://doi.org/10.1063/1.3489925)

**Features**: 
- Implemented two algorithms:
    - Explicit matrix multiplication algorithm. 
    - Fast Fourier Transform algorithm.

**Usage**:
- On how to use this code, see `test.cpp`.
- Consistency between two algorithms, see `test_consistency.cpp`.
- To compare the efficiency of the two algorithms, see `test_benchmark.cpp`.
- Note that: the FFT algorithm will start to win over explicit DFT matrix method after `nbeads` exceeds `40`.

**Dependency**:
- `FFTW3`: FFT library
- `Eigen3`: Linear Algebra

---

Shout out to these packages for inspirations:
- [`NQCDynamics.jl`](https://github.com/NQCD/NQCDynamics.jl)
- [`MAVARIC`](https://github.com/AnanthGroup/MAVARIC)
