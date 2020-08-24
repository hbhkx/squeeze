#include <vector>
#include <valarray>
#include <iostream>
#include "Squeeze"
// #include <omp.h>
// #include <mkl_cblas.h>
using namespace Squeeze;

int main() {
#define N 20
  double* ptr;

  std::array<double, N> arr;
  for (int i = 0; i < N; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;

  Vector<double> v(N);
  for (int i = 0; i < N; i++) {
    v[i] = arr[i];
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
  ptr = v.data();
  v.~Vector();

  new (&v) Vector<double>(N);
  for (int i = 0; i < N; i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;
  std::cout << (v.data() == ptr) << std::endl;
  std::cout << std::endl;

  std::valarray<double> valarr(N);
  for (int i = 0; i < N; i++) {
    valarr[i] = arr[i];
    std::cout << valarr[i] << " ";
  }
  std::cout << std::endl;
  ptr = std::begin(valarr);
  valarr.~valarray();

  new (&valarr) std::valarray<double>(N);
  for (int i = 0; i < N; i++) {
    std::cout << valarr[i] << " ";
  }
  std::cout << std::endl;
  std::cout << (std::begin(valarr) == ptr) << std::endl;
  std::cout << std::endl;

  std::vector<double, AlignedAllocator<double>> vec(N);
  vec[0] = 2;
  vec[N-1] = N;
  for (int i = 0; i < N; i++)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
  ptr = vec.data();
  vec.~vector();
  std::cout << *ptr << std::endl;

  new (&vec) std::vector<double, AlignedAllocator<double>>(N);
  for (int i = 0; i < N; i++)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
  std::cout << (vec.data() == ptr) << std::endl;
  std::cout << std::endl;
}
