
cmake_minimum_required(VERSION 3.5)

project(ppcdisasm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(ppcdisasm SHARED src/ppc-dis.cpp src/ppc-opc.c)
target_include_directories(ppcdisasm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)

add_executable(benchmark src/benchmark.cpp)
target_include_directories(benchmark PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(
  benchmark
  GTest::gtest_main
  ppcdisasm
)

install(TARGETS ppcdisasm DESTINATION lib)

enable_testing()

add_executable(disas_test test/disas_test.cpp)
target_include_directories(disas_test PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(
  disas_test
  GTest::gtest_main
  ppcdisasm
)

include(GoogleTest)
gtest_discover_tests(disas_test)