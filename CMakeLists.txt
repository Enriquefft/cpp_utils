cmake_minimum_required(VERSION 3.25.2)
project(my_utils
  VERSION 1
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(my_utils src/Sign.cpp src/RandomNum.cpp)

target_include_directories(my_utils PRIVATE .)

set(UTILS_HEADERS
  include/Sign.hpp
  include/RandomNum.hpp
  include/PrintableContainer.hpp
)

set_target_properties(
  my_utils
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "${UTILS_HEADERS}")

include(GNUInstallDirs)

install(
  TARGETS my_utils
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/my_utils
  PUBLIC_HEADER
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/my_utils)
