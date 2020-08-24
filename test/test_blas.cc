#include <ctime>
#include <iostream>
#include "../src/Squeeze"
#include <numeric>
#include <omp.h>
#include <mkl.h>
using namespace Squeeze;

int main() {
  Idx N = 1024 * 1024;
  Idx n = 232342835 % N;
  Vector<float> vec1(N), vec2(N);
  VSLStreamStatePtr stream;
  vslNewStream(&stream, VSL_BRNG_SFMT19937, std::time(nullptr));
  vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, N,
                reinterpret_cast<float*>(vec1.data()), 0, 1024);
  vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, stream, N,
                reinterpret_cast<float*>(vec2.data()), 0, 1024);
  vslDeleteStream(&stream);

  double start, end;

  // for (Idx i = 0; i < N; i++) {
  //   std::cout << vec2[i] << ' ';
  // }
  std::cout << -2 * vec1[n] + vec2[n] << std::endl;
  vec2 += -vec1 * 2;
  // for (Idx i = 0; i < N; i++) {
  //   std::cout << vec2[i] << ' ';
  // }
  std::cout << vec2[n] << std::endl;
}
