# NormalModeCartesianTransformation

`c++` package for ring polymer coordinates transformation, between cartesian and normal mode coordinates.

The convention for the FFT matrix follows Eq.(18) in article "Efficient stochastic thermostatting of path integral molecular dynamics." [JCP2010](https://doi.org/10.1063/1.3489925)

Features: 
- Implemented two algorithms:
    - Explicit matrix multiplication algorithm. 
    - Fast Fourier Transform algorithm.

Notes: 
When you have more than 50 ring polymer beads, using the FFT algorithm will be increasingly beneficial.

Dependency:
- FFTW3: FFT library
- Eigen3: Linear Algebra

Shout out to these packages for inspirations:
- [`NQCDynamics.jl`](https://github.com/NQCD/NQCDynamics.jl)
- [`MAVARIC`](https://github.com/AnanthGroup/MAVARIC)
