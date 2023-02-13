#include <concepts>

namespace my_utils {

template <std::unsigned_integral T>
constexpr auto UnsignedToSigned(const T &value);

template <std::signed_integral T>
constexpr auto SignedToUnsigned(const T &value);

// U -> S instantiations
extern template auto UnsignedToSigned(const unsigned int &value);
extern template auto UnsignedToSigned(const unsigned long &value);

// S -> U instantiations
extern template auto SignedToUnsigned(const int &value);
extern template auto SignedToUnsigned(const long &value);

} // namespace my_utils
