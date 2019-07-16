#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "Eigen/Sparse"
using namespace std;

typedef Eigen::Triplet<unsigned long> T;

Eigen::SparseMatrix<unsigned long> readgrapgh(string path)
{
    vector<T> tripletList;
    vector<unsigned long> L;
    vector<unsigned long> R;
    unsigned long max_L, max_R;
    max_L = 0;
    max_R = 0;
    
    FILE * f = fopen(path.c_str(), "r");
    if(!f) {
        cerr << "Problem reading binary input file: " << path << endl;
    }
    fseek(f, 0L, SEEK_END); 
  
    // Get the size of the input file and number of non-zeros 
    int res = ftell(f); 
    int nnz = res/(sizeof(int)*2);

    double start = omp_get_wtime( );
    cout << "Reading matrix with " << nnz << " nonzeros" << endl;

    int *rowindices = new int[nnz];
    int *colindices = new int[nnz];
    
    // go back to beginning of file
    fseek(f, 0L, SEEK_SET); 
    size_t rows = fread(rowindices, sizeof(int), nnz, f);
    size_t cols = fread(colindices, sizeof(int), nnz, f);
    // closing the file 
    fclose(f); 

    for (int i=0; i<nnz; i++){
        int a = rowindices[i];
        int b = colindices[i];
        L.push_back(a);
        R.push_back(b);
        max_L = (a > max_L) ? a : max_L;
        max_R = (b > max_R) ? b : max_R;
    }
    
    delete rowindices;
    delete colindices;

    //cout << "maxL " << max_L << endl;
    //cout << "maxR " << max_R << endl;
    
    Eigen::SparseMatrix<unsigned long> A(max_L, max_R);
    tripletList.reserve(nnz);
    for (auto i = 0; i < nnz; i++)
    {
        tripletList.push_back(T(L[i] - 1, R[i] - 1, 1));
    }
    A.setFromTriplets(tripletList.begin(), tripletList.end());

    if (max_L < max_R)
    {
        return A;
    }
    else
    {
        return A.transpose();
    }

}

int main(int argc, char* argv[])
{
    string path = argv[1];

    cout << "Loading data \n";
    Eigen::SparseMatrix<unsigned long> A = readgrapgh(path);    //Read graph


    cout << "Start calculation \n";
    auto start = chrono::high_resolution_clock::now();


    Eigen::SparseMatrix<unsigned long> B = A * A.transpose();        //  A x A transpose
    cout << "A x A transpose\n";


    auto size = B.rows();

    for (auto i = 0; i < size; i++) { B.coeffRef(i, i) = 0; }    //Set diag(A) = 0
    cout << "Set diag(A) = 0\n";


    B = B.cwiseProduct(B) - B;        // (B Elementwise Product B) - B
    cout << "(B Elementwise Product B) - B\n";


    cout << B.sum() / 4<<'\n';


    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Time: " << elapsed.count() << " s\n";
}

