cmake_minimum_required(VERSION 3.10)
project(simple_fuzzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common flags for all builds
set(COMMON_FLAGS "-g -O1")

# Library without fuzzing
add_library(parser
    src/parser.cpp
)

# Fuzzer executable with special flags
add_executable(fuzzing
    src/fuzzing.cpp
)
target_link_libraries(fuzzing PRIVATE parser)
set_target_properties(fuzzing PROPERTIES
    COMPILE_FLAGS "${COMMON_FLAGS} -fsanitize=fuzzer,address"
    LINK_FLAGS "-fsanitize=fuzzer,address"
)
