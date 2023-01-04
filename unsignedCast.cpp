#include "utils.h"
#include <limits>
#include <stdexcept>

template <typename T> unsigned int utils::unsignedCast(T number) {
  T min = std::numeric_limits<unsigned int>::min();
  T max = static_cast<T>(std::numeric_limits<unsigned int>::max());

  if (number < min || number > max) {
    throw std::out_of_range("Number is out of range");
  }

  return static_cast<unsigned int>(number);
}

// explicit instanciation

template unsigned int utils::unsignedCast<int>(int);
template unsigned int utils::unsignedCast<long>(long);
template unsigned int utils::unsignedCast<unsigned int>(unsigned int);
template unsigned int utils::unsignedCast<unsigned long>(unsigned long);
template unsigned int utils::unsignedCast<float>(float);
template unsigned int utils::unsignedCast<double>(double);
