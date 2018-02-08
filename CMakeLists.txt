cmake_minimum_required(VERSION 3.7)
project(server)

set(CMAKE_CXX_STANDARD 14)
set (Boost_USE_STATIC_LIBS ON)

file(GLOB sources
    ${PROJECT_SOURCE_DIR}/sources/*.h
    ${PROJECT_SOURCE_DIR}/sources/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} pthread)
