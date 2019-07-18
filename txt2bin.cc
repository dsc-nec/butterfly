#include <frovedis/matrix/crs_matrix.hpp>
#include <frovedis/matrix/spgemm.hpp>

using namespace std;
using namespace frovedis;

int main(int argc, char* argv[]) {
  char* fname = argv[1];
  char newfname[128];
  // make second argument true in case of 0-based index
  auto crs = make_crs_matrix_local_loadcoo<int,int>(fname);
  snprintf(newfname, 128, "%s.data", fname);
  crs.savebinary(newfname);
}

