#include "include/RandomNum.hpp"

#include <random>
#include <stdexcept>

namespace my_utils {

template <arithmetic_t T>
RandomNum<T>::RandomNum(const T &min, const T &max) : m_min(min), m_max(max) {
  if (m_min > m_max) {
    throw std::invalid_argument("min > max");
  }
}
template <arithmetic_t T>
RandomNum<T>::RandomNum(const range_t<T> &range)
    : m_min(range.first), m_max(range.second) {
  if (m_min > m_max) {
    throw std::invalid_argument("min > max");
  }
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

// explicit instantiation

// clang-format off
template class RandomNum<int>;
template class RandomNum<uint>;
template class RandomNum<float>;
template class RandomNum<int8_t>;
template class RandomNum<uint8_t>;

} // namespace my_utils
