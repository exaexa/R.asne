
# R.asne, the A-tSNE for R

Approximated tSNE as defined in:

Pezzotti, N., Lelieveldt, B. P., van der Maaten, L., Höllt, T., Eisemann, E., & Vilanova, A. (2017). Approximated and user steerable tSNE for progressive visual analytics. IEEE transactions on visualization and computer graphics, 23(7), 1739-1752.

## Installing

- clone install the High Dimensionality Inspector from here: https://github.com/Nicola17/High-Dimensional-Inspector . Remember where you installed it (the `-DCMAKE_INSTALL_PREFIX` variable). Step by step:
  1. `cd High-Dimensionality-Inspector`
  2. `mkdir build; cd build`
  3. `cmake -DCMAKE_INSTALL_PREFIX=/home/YOURNAME/.local ..`  (fill in your name; optional prefix is `/usr/local` if you have the privilege). You also want to pass some optimizer options, like `-DCMAKE_CXX_FLAGS=-O3`. You will likely also need the CRoaring library, which is available from here: https://github.com/RoaringBitmap/CRoaring
  4. `make -jN && make install` (fill in your number of available CPUs)
- clone the R.asne repository
- go to the src folder, edit `Makefile` and fill in the path to where you installed the High-Dimensionality-Inspector. If you installed to `/usr/local`, you probably don't need anything.
- Install R.asne using devtools: `library(devtools); install('R.asne')`

## Using the stuff

Let's say you've got the MNIST dataset in raw binary floats.
```
m <- t(matrix(readBin("mnist.in", "double", size=4, n=28*28*1000), nrow=28*28, ncol=1000))
library(asne)

res <- ASNE(m)
plot(res$embedding[,1],res$embedding[,2])
```

