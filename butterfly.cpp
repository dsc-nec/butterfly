#include <frovedis/matrix/crs_matrix.hpp>
#include <frovedis/matrix/spgemm.hpp>
#include <numeric>
#include <string>
#include <chrono>

using namespace std;
using namespace frovedis;

int main(int argc, char* argv[])
{
        string path = argv[1];

        // Load file
        cout << "Loading data \n";
        //auto A = make_crs_matrix_local_load<int,int>(path);
        auto A = make_crs_matrix_local_loadbinary<int,int>(path);

        cout << "Start calculation \n";
        auto start = chrono::high_resolution_clock::now();

        cout << "Before transposing...";
        // A transpose x A
        auto tmp = A.transpose();
        cout << "After transposing...";
        auto B = spgemm(A,tmp);
        cout << "After spgemm...";
        // Set diag(A) = 0, TO DO!
        set_diag_zero(B);
        cout << "After setting diag zero...";
        // sum (x^2 - x)
        auto sum = inner_product(B.val.begin(), B.val.end(), B.val.begin(), 0) - accumulate(B.val.begin(), B.val.end(), 0);
        cout << "After inner_product...";
        cout << sum/4 << endl;
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << "Time: " << elapsed.count() << " s\n";
}

