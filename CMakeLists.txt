# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.18)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the project name
project(StereoVisionProject CXX)

# Find OpenCV package
# You might need to set OpenCV_DIR environment variable if CMake can't find it automatically.
# Example: export OpenCV_DIR=/path/to/your/opencv/build
find_package(OpenCV REQUIRED)

# Check if OpenCV was found. If not, print an error and exit.
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please set OpenCV_DIR to your OpenCV build directory.")
endif()

# Print the OpenCV version found (optional, for verification)
message(STATUS "OpenCV found. Version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# Add an executable target for your project
# This assumes your main source file is main.cpp
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the executable with OpenCV libraries
# This ensures your program can use OpenCV functions
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Add OpenCV include directories so your compiler can find OpenCV headers
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS} include)

# Optional: Set C++ standard (e.g., C++14 or C++17)
# Using a modern C++ standard is good practice
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

