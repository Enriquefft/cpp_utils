#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <cstdint>
#include <utility> // std::pair

using uint = unsigned int;

namespace my_utils {

template <typename T> using range_t = std::pair<T, T>;

template <typename T>
concept arithmetic_t = std::is_arithmetic_v<T>;

template <arithmetic_t T> class RandomNum {
public:
  explicit RandomNum(const range_t<T> &range);
  RandomNum(const T &min, const T &max);

  T operator()()
    requires std::integral<T>;
  T operator()()
    requires std::floating_point<T>;

private:
  T m_min;
  T m_max;
};

template <std::unsigned_integral T>
constexpr auto UnsignedToSigned(const T &value);

template <std::signed_integral T>
constexpr auto SignedToUnsigned(const T &value);

// clang-format off
extern template class RandomNum<int>;
extern template class RandomNum<uint>;
extern template class RandomNum<float>;
extern template class RandomNum<int8_t>;
extern template class RandomNum<uint8_t>;

} // namespace my_utils

#endif // !MY_UTILS_H
