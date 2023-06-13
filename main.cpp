#include <iostream>

#include "matrix.hpp"

int main() {
  Matrix<int> a(2, 2, 4);
  Matrix<int> b(2, 2, 8);

  Matrix<int> c(2, 2, 12);

  Matrix<int> res = a.seq_add(b);

  std::cout << (res == c) << '\n';

  std::cout << a << '\n';

  std::cout << "Result:\n";
  std::cout << res << '\n';

  std::cout << "C:\n";
  std::cout << c << '\n';

  return 0;
}
