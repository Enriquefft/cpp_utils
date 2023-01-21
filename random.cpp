#include "my_utils.h"

#include <random>
#include <stdexcept>

namespace my_utils {

using std::uniform_int_distribution;
using std::uniform_real_distribution;

template <std::integral T> T RandomNum(const T &min, const T &max) {
  if (min >= max) {
    throw std::invalid_argument(
        "El primer valor del rango debe ser menor al segundo");
  }

  std::random_device r_d;
  std::default_random_engine generator(r_d());

  uniform_int_distribution<T> rand_num(min, max);

  return rand_num(generator);
}
template <std::floating_point T> T RandomNum(const T &min, const T &max) {
  if (min >= max) {
    throw std::invalid_argument(
        "El primer valor del rango debe ser menor al segundo");
  }

  std::random_device r_d;
  std::default_random_engine generator(r_d());

  uniform_real_distribution<T> rand_num(min, max);

  return rand_num(generator);
}

// explicit instantiation

// clang-format off
template int     RandomNum<int>   (const int    &min, const int    &max);
template float   RandomNum<float> (const float  &min, const float  &max);
template double  RandomNum<double>(const double &min, const double &max);
template uint    RandomNum<uint>  (const uint   &min, const uint   &max);
template ulong   RandomNum<ulong> (const ulong  &min, const ulong  &max);

} // namespace my_utils
