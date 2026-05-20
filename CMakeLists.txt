cmake_minimum_required(VERSION 3.20)
project(oms_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(oms_cpp
  main.cpp
  Orderbook.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SOURCE_SUBDIR googletest-1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(oms_cpp_tests
  tests/OrderbookTests.cpp
)
target_sources(oms_cpp_tests PRIVATE
  Orderbook.cpp
)
target_include_directories(oms_cpp_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(oms_cpp_tests
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(oms_cpp_tests)
