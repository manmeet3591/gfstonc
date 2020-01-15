#!/bin/bash
source activate py35
./configure --prefix=/home/manmeet/Documents/gfstonc/lib --enable-python
make
make install
export SHTNS_LIBDIR=/home/manmeet/Documents/gfstonc/lib/lib
cp libshtns.a /home/manmeet/Documents/gfstonc/lib/lib 
