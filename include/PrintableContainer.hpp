#ifndef PRINTABLE_CONTAINER_HPP
#define PRINTABLE_CONTAINER_HPP

#ifdef WIN32
#include <windows.h>
#else
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>    // for STDOUT_FILENO
#endif

#include <algorithm>
#include <cmath>
#include <iostream>

// clang-format off

// https://en.cppreference.com/w/cpp/container
template<typename T>
concept PrintableContainer = requires(T cont) {
    typename T::value_type;
    typename T::size_type;
    typename T::difference_type;
    typename T::reference;
    typename T::const_reference;

    // iterable
    {cont.cbegin () }   -> std::convertible_to<typename T::const_iterator>;
    {cont.cend   () }   -> std::convertible_to<typename T::const_iterator>;

    // container
    {cont.empty  () }   -> std::convertible_to<bool>;
    {cont.size   () }   -> std::convertible_to<typename T::size_type>;
    {cont.max_size() }  -> std::convertible_to<typename T::size_type>;
    {cont.empty  () }   -> std::convertible_to<bool>;

} &&
// value_type is printable
requires(typename T::value_type val) {
    {std::cout << val} -> std::convertible_to<std::ostream&>;
} &&

// disable for std::basic_string
!std::is_same_v<T, std::basic_string<typename T::value_type>>;
;
// clang-format on

// Container of containers
template <typename T>
concept PrintableNestedContainer = PrintableContainer<typename T::value_type>;

// generic ostream overload
template <PrintableContainer T>
std::ostream &operator<<(std::ostream &ost, const T &container) {

  if (container.empty()) {
    return ost;
  }

  uint8_t window_width = 0;
#ifdef WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  window_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
  struct winsize size {};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // NOLINT
  window_width = static_cast<uint8_t>(size.ws_col);
#endif

  if (window_width == 0) {
    throw std::runtime_error("Could not get window width");
  }

  // How many elements can fit in a line
  uint8_t elem_fit = 0;

  if constexpr (std::is_arithmetic_v<typename T::value_type>) {

    auto [min_v, max_v] =
        std::minmax_element(container.begin(), container.end());

    uint8_t max_num_size =
        std::max(trunc(log10(*min_v)) + 1, trunc(log10(*max_v)) + 1);

    elem_fit = window_width / (max_num_size + 2);

  } else {
    elem_fit = window_width / 3;
  }

  if (container.size() <= elem_fit) {
    for (const auto &item : container) {
      ost << item;
      if (&item != &container.back()) {
        ost << ", ";
      }
    }
  } else {

    uint8_t counter = 0;
    for (const auto &item : container) {

      ost << item;
      if (&item != &container.back()) {
        ost << ", ";
      }
      if (counter >= elem_fit) {
        ost << std::endl;
        counter = 0;
      }
      counter++;
    }
  }

  return ost;
}

template <PrintableNestedContainer T>
std::ostream &operator<<(std::ostream &ost, const T &container) {

  for (const auto &item : container) {
    ost << item << std::endl;
  }

  return ost;
}

#endif // PRINTABLE_CONTAINER_HPP
