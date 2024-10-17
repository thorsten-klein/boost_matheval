cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project(boost_matheval CXX)

include(GNUInstallDirs)

# Default build type is Debug
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type" FORCE)
endif()

# Add local package finders
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Build options
option(WITH_COVERAGE "Generate code coverage report" OFF)
if(WITH_COVERAGE)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    link_libraries(gcov)
  else()
    message(WARNING "Coverage information only supported on GCC")
  endif()
endif()

option(WITH_CLANG_TIDY "Run Clang-Tidy during compilation" OFF)

# Find clang-tidy executable (no matter if building with gcc or clang)
string(REGEX REPLACE "^([1-9]+\\.[0-9]+).*$" "\\1" CLANG_MINOR_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy-${CLANG_MINOR_VERSION}" "clang-tidy"
    DOC "Path to clang-tidy executable"
)

if(WITH_CLANG_TIDY)
  if(NOT CLANG_TIDY_EXE)
    message(FATAL_ERROR "clang-tidy was enabled but no executable found.")
  else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
      "-checks=-*,bugprone-*,cert-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,performance-*,readability-*"
      "-header-filter=.*"
      "-warnings-as-errors=*"
    )
  endif()
endif()


# Subdirectories
add_subdirectory(src/qi)
add_subdirectory(src/x3)
add_subdirectory(doc/doxygen)
add_subdirectory(examples)
add_subdirectory(tests)



# Install
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    EXPORT ${PROJECT_NAME}
    NAMESPACE   matheval::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}/
)

