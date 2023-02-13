#include "include/RandomNum.hpp"

#include <random>
#include <stdexcept>

namespace my_utils {

template <arithmetic_t T>
static inline void ValidateInput(const T &min, const T &max) {
  if (min > max) {
    throw std::invalid_argument("min can't be greater than max");
  }
}

template <arithmetic_t T>
RandomNum<T>::RandomNum(const T &min, const T &max) : m_min(min), m_max(max) {
  ValidateInput(m_min, m_max);
}
template <arithmetic_t T>
RandomNum<T>::RandomNum(const range_t<T> &range)
    : m_min(range.first), m_max(range.second) {
  ValidateInput(m_min, m_max);
}

template <arithmetic_t T>
T RandomNum<T>::operator()()
  requires std::integral<T>
{
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_int_distribution<T>{m_min, m_max}(gen);
}
template <arithmetic_t T>
T RandomNum<T>::operator()()
  requires std::floating_point<T>
{
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_real_distribution<T>{m_min, m_max}(gen);
}

template <arithmetic_t T>
T RandomNum_v(const T &min, const T &max)
  requires std::integral<T>
{
  ValidateInput(min, max);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_int_distribution<T>{min, max}(gen);
}

template <arithmetic_t T>
T RandomNum_v(const T &min, const T &max)
  requires std::floating_point<T>
{
  ValidateInput(min, max);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_real_distribution<T>{min, max}(gen);
}

// clang-format off
// class explicit instantiation

template class RandomNum<int>;
template class RandomNum<uint>;
template class RandomNum<float>;
template class RandomNum<int8_t>;
template class RandomNum<uint8_t>;

// function explicit instantiation
template int     RandomNum_v<int>    (const int     &, const int&);
template uint    RandomNum_v<uint>   (const uint    &, const uint&);
template float   RandomNum_v<float>  (const float   &, const float&);
template int8_t  RandomNum_v<int8_t> (const int8_t  &, const int8_t&);
template uint8_t RandomNum_v<uint8_t>(const uint8_t &, const uint8_t&);


} // namespace my_utils
