#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdexcept>
#include <sys/uio.h> // uint & ulong
#include <type_traits>
#include <utility> // std::pair

namespace my_utils {

template <typename T> using range_t = const std::pair<T, T> &;

template <std::integral T> T RandomNum(const T &min, const T &max);
template <std::floating_point T> T RandomNum(const T &min, const T &max);

template <std::integral T> inline T RandomNum(range_t<T> rango) {
  return RandomNum<T>(rango.first, rango.second);
}
template <std::floating_point T> inline T RandomNum(range_t<T> rango) {
  return RandomNum<T>(rango.first, rango.second);
}

template <std::unsigned_integral T>
inline constexpr auto UnsignedToSigned(const T &value) {
  auto max = std::numeric_limits<std::make_signed_t<T>>::max();
  if (value > static_cast<T>(max)) {
    throw std::out_of_range("Value is out of range");
  }
  return static_cast<std::make_signed_t<T>>(value);
}

template <std::signed_integral T>
inline constexpr auto SignedToUnsigned(const T &value) {
  if (value < 0) {
    throw std::invalid_argument("Value must be positive");
  }
  return static_cast<std::make_unsigned_t<T>>(value);
}

// clang-format off
extern template int     RandomNum<int>   (const int    &min, const int    &max);
extern template float   RandomNum<float> (const float  &min, const float  &max);
extern template double  RandomNum<double>(const double &min, const double &max);
extern template uint    RandomNum<uint>  (const uint   &min, const uint   &max);
extern template ulong   RandomNum<ulong> (const ulong  &min, const ulong  &max);

} // namespace my_utils

#endif // !MY_UTILS_H
