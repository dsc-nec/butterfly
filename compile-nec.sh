#!/bin/bash
source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

make -f Makefile-nec cleandist
make -f Makefile-nec
make -f Makefile-nec clean
