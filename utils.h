#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <utility>

namespace utils {

template <typename T> unsigned int unsignedCast(T number);

template <typename T>
concept Integral = std::is_integral<T>::value;

template <typename T>
concept FloatingPoint = std::is_floating_point<T>::value;

template <Integral T> T GenerarRandomNum(std::pair<T, T> rango);
template <FloatingPoint T> T GenerarRandomNum(std::pair<T, T> rango);

} // namespace utils

#endif // !UTILS_H
