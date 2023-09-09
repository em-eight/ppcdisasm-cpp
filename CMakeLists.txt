
cmake_minimum_required(VERSION 3.5)

project(ppcdisasm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

if(BUILD_SHARED)
add_library(ppcdisasm SHARED src/ppc-dis.cpp src/ppc-opc.c)
else()
add_library(ppcdisasm src/ppc-dis.cpp src/ppc-opc.c)
endif()
target_include_directories(ppcdisasm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)

install(TARGETS ppcdisasm DESTINATION lib)

if(BUILD_TESTING)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(benchmarkDecode src/benchmarkDecode.cpp)
target_include_directories(benchmarkDecode PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(
  benchmarkDecode
  ppcdisasm
)

add_executable(genOpIds src/genOpIds.cpp)
target_include_directories(benchmarkDecode PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(
  genOpIds
  ppcdisasm
)

add_executable(benchmarkDisassemble src/benchmarkDisassemble.cpp)
target_include_directories(benchmarkDisassemble PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
target_link_libraries(
  benchmarkDisassemble
  ppcdisasm
)

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
endif()
