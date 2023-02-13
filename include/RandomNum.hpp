#ifndef RANDOM_NUM_HPP
#define RANDOM_NUM_HPP

#include <cstdint>
#include <utility> // std::pair

using uint = unsigned int;
using ulong = uint64_t;

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

template <arithmetic_t T> T RandomNum_v(const T &min, const T &max);

template <arithmetic_t T> inline T RandomNum_v(const range_t<T> &range) {
  return RandomNum_v(range.first, range.second);
}

// clang-format off
// class explicit instantiation

extern template class RandomNum<int>;
extern template class RandomNum<uint>;
extern template class RandomNum<float>;
extern template class RandomNum<int8_t>;
extern template class RandomNum<uint8_t>;

// function explicit instantiation
extern template int     RandomNum_v<int>    (const int     &, const int&);
extern template uint    RandomNum_v<uint>   (const uint    &, const uint&);
extern template float   RandomNum_v<float>  (const float   &, const float&);
extern template int8_t  RandomNum_v<int8_t> (const int8_t  &, const int8_t&);
extern template uint8_t RandomNum_v<uint8_t>(const uint8_t &, const uint8_t&);

} // namespace my_utils

#endif // !RANDOM_NUM_HPP
