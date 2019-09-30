cmake_minimum_required(VERSION 3.4)

# Create new Visual Studio solution
project(FFT_BENCHMARK CXX)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Setup Release version
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Find OpenCV installation folder
find_package(OpenCV REQUIRED)

set(LIBRARY_DEPS ${OpenCV_LIBS})

# Move executable files 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)


# Generate projects
set(SRC_TEST 
    src/common.h
    src/test.cpp)

add_executable(Test ${SRC_TEST})
target_link_libraries(Test ${LIBRARY_DEPS})