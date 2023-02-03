#include "include/Sign.hpp"

#include <limits>
#include <stdexcept>

namespace my_utils {

template <std::unsigned_integral T>
constexpr auto UnsignedToSigned(const T &value) {
  auto max = std::numeric_limits<std::make_signed_t<T>>::max();
  if (value > static_cast<T>(max)) {
    throw std::out_of_range("Value is out of range");
  }
  return static_cast<std::make_signed_t<T>>(value);
}

template <std::signed_integral T>
constexpr auto SignedToUnsigned(const T &value) {
  if (value < 0) {
    throw std::invalid_argument("Value must be positive");
  }
  return static_cast<std::make_unsigned_t<T>>(value);
}

// Explicit instantiations
template auto UnsignedToSigned(const unsigned int &value);

} // namespace my_utils
