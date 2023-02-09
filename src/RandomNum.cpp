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

/*

*/

template <arithmetic_t T>
T RandomNum<T>::operator()(const T &min, const T &max)
  requires std::integral<T>
{
  ValidateInput(min, max);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_int_distribution<T>{min, max}(gen);
}

template <arithmetic_t T>
T RandomNum<T>::operator()(const T &min, const T &max)
  requires std::floating_point<T>
{
  ValidateInput(min, max);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_real_distribution<T>{min, max}(gen);
}

template <arithmetic_t T>
T RandomNum<T>::operator()(const range_t<T> &range)
  requires std::integral<T>
{
  ValidateInput(range.first, range.second);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_int_distribution<T>{range.first, range.second}(gen);
}

template <arithmetic_t T>
T RandomNum<T>::operator()(const range_t<T> &range)
  requires std::floating_point<T>
{
  ValidateInput(range.first, range.second);
  static std::default_random_engine gen{std::random_device{}()};
  return std::uniform_real_distribution<T>{range.first, range.second}(gen);
}
// explicit instantiation

// clang-format off
template class RandomNum<int>;
template class RandomNum<uint>;
template class RandomNum<float>;
template class RandomNum<int8_t>;
template class RandomNum<uint8_t>;

} // namespace my_utils
