#ifndef SEQUENCE_CONTAINER_HPP
#define SEQUENCE_CONTAINER_HPP

#ifdef WIN32
#include <windows.h>
#else
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>    // for STDOUT_FILENO
#endif

#include <algorithm>
#include <cmath>
#include <concepts>
#include <ostream>

// clang-format off

// https://en.cppreference.com/w/cpp/named_req/SequenceContainer
template<typename T>
concept SequenceContainer = requires(T cont) {
    typename T::value_type;
    typename T::size_type;
    typename T::difference_type;
    typename T::reference;
    typename T::const_reference;
    {cont.empty  () }   -> std::convertible_to<bool>;
    {cont.size   () }   -> std::convertible_to<typename T::size_type>;
    {cont.front  () }   -> std::convertible_to<typename T::reference>;
    {cont.back   () }   -> std::convertible_to<typename T::reference>;
    {cont.begin  () }   -> std::convertible_to<typename T::iterator>;
    {cont.end    () }   -> std::convertible_to<typename T::iterator>;
    {cont.cbegin () }   -> std::convertible_to<typename T::const_iterator>;
    {cont.cend   () }   -> std::convertible_to<typename T::const_iterator>;
    {cont.rbegin () }   -> std::convertible_to<typename T::reverse_iterator>;
    {cont.rend   () }   -> std::convertible_to<typename T::reverse_iterator>;
    {cont.crbegin() }   -> std::convertible_to<typename T::const_reverse_iterator>;
    {cont.crend  () }   -> std::convertible_to<typename T::const_reverse_iterator>;
} &&
// disable for std::basic_string
!std::is_same_v<T, std::basic_string<typename T::value_type>>;
;
// clang-format on

// Container of containers
template <typename T>
concept ContainerOfSequenceContainer =
    SequenceContainer<typename T::value_type> && SequenceContainer<T>;

static inline uint8_t GetTerminalWidth() {
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
    throw std::runtime_error("Could not get terminal width");
  }
  return window_width;
}

// generic ostream overload
template <SequenceContainer T>
std::ostream &operator<<(std::ostream &ost, const T &container) {

  if (container.empty()) {
    ost << "Empty container";
    return ost;
  }

  // if T is vector
  if constexpr (std::is_same_v<T, std::basic_string<typename T::value_type>>) {
    ost << "PRINTING BASIC STRING\n";
    ost << container;
    return ost;
  }
  constexpr bool IS_ARITHMETIC = std::is_arithmetic_v<typename T::value_type>;

  uint8_t window_width = GetTerminalWidth();

  // How many elements can fit in a line
  uint8_t elem_fit = 0;

  if constexpr (IS_ARITHMETIC) {

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

    ost << "Container is too big to fit in one line" << std::endl;
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

  ost << std::endl << static_cast<int>(window_width);

  return ost;
}

template <ContainerOfSequenceContainer T>
std::ostream &operator<<(std::ostream &ost, const T &container);

#endif // SEQUENCE_CONTAINER_HPP
