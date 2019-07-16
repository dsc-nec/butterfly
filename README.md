# butterfly
butterfly counting in bipartite graph

### directory structure
source code is in butterfly.cpp

Eigen has the 3rd party library required to compile the code.

### How to build the code
To build for NEC machine:

    ./compile-nec.sh

To build for Intel CPU machine:

    make

### How to run
    ./butterfly-nec.bin <input_file.data>

### Where are the testing dataset?
The original dataset were downloaded from http://konect.uni-koblenz.de/, which is used by the butterfly counting paper in our reference. The datasets have been preprocessed (to remove unnecessary weight; removing duplicated edges) and converted to binary format to facilitate the reading from NEC machine.

The datasets are tempararily hosted at:

    http://129.79.186.230/graphdata/butterfly/
