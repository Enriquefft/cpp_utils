#include "utils.h"

#include <random>
#include <stdexcept>

template <utils::Integral T> T utils::GenerarRandomNum(std::pair<T, T> rango) {

  if (rango.first >= rango.second) {
    throw std::invalid_argument(
        "El primer valor del rango debe ser menor al segundo");
  }

  std::random_device r_d;
  std::default_random_engine generator(r_d());

  std::uniform_int_distribution<T> rand_num(rango.first, rango.second);

  return rand_num(generator);
}

template <utils::FloatingPoint T>
T utils::GenerarRandomNum(std::pair<T, T> rango) {

  if (rango.first >= rango.second) {
    throw std::invalid_argument(
        "El primer valor del rango debe ser menor al segundo");
  }

  std::random_device r_d;
  std::default_random_engine generator(r_d());

  std::uniform_real_distribution<T> rand_num(rango.first, rango.second);

  return rand_num(generator);
}

// explicit instantiation

template int utils::GenerarRandomNum<int>(std::pair<int, int> rango);
template float utils::GenerarRandomNum<float>(std::pair<float, float> rango);
template double
utils::GenerarRandomNum<double>(std::pair<double, double> rango);
template long double
utils::GenerarRandomNum<long double>(std::pair<long double, long double> rango);
template unsigned int utils::GenerarRandomNum<unsigned int>(
    std::pair<unsigned int, unsigned int> rango);
template unsigned long utils::GenerarRandomNum<unsigned long>(
    std::pair<unsigned long, unsigned long> rango);
