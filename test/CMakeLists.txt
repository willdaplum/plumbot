cmake_minimum_required(VERSION 3.14...3.22)

project(PlumbotTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  GIT_TAG v1.14.0
)
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(Plumbot REQUIRED)
else()
  CPMAddPackage(NAME Plumbot SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main Plumbot)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(Plumbot PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(Plumbot PUBLIC /W4 /WX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add PlumbotTests ----

enable_testing()


# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(Plumbot PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(Plumbot PUBLIC -fprofile-arcs -ftest-coverage)
endif()
