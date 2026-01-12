cmake_minimum_required(VERSION 3.10)
project(BMP_Processor C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(bmp-processor
    src/main.c
    src/bmp_utils.c
)

# Optional: Add testing
enable_testing()
add_subdirectory(tests)
