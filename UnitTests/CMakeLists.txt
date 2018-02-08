cmake_minimum_required(VERSION 3.7)
project(tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

file(GLOB test_sources
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../sources/)

file(GLOB sources
    ${PROJECT_SOURCE_DIR}/../sources/tcp*
    ${PROJECT_SOURCE_DIR}/../sources/request*)

add_executable(${PROJECT_NAME} ${test_sources} ${sources})

target_link_libraries(${PROJECT_NAME} pthread ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
