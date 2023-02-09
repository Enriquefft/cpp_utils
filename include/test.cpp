#include "RandomNum.hpp"
#include <iostream>
int main(int argc, char *argv[]) {

  std::cout << my_utils::RandomNum<int>(1, 4);
  return 0;
}
