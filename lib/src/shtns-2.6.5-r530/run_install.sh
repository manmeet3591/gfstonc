#!/bin/bash
source activate py27
./configure --prefix=/home/manmeet/Documents/gfstonc/lib --enable-python
make
make install-lib
export SHTNS_LIBDIR=/home/manmeet/Documents/gfstonc/lib/lib
cp libshtns_omp.a /home/manmeet/Documents/gfstonc/lib/lib/libshtns.a
