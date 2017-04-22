cmake_minimum_required(VERSION 3.4.0)
project(luacpp_test)

get_filename_component(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
set(CATCH "${TOP_DIR}/contrib/Catch")
set(SRC "${TOP_DIR}/src")

find_package(Lua51 REQUIRED)

include_directories(
  ${TOP_DIR}/include
  ${CATCH}/include
  ${LUA_INCLUDE_DIR}
)

set(TEST_SOURCES
  luacpp_test.cpp)

add_executable(luacpp_test
  ${TEST_SOURCES})

target_compile_definitions(luacpp_test PUBLIC "CATCH_CONFIG_MAIN" "CATCH_CONFIG_COLOUR_NONE")
target_link_libraries(luacpp_test ${LUA_LIBRARIES})
add_test(CommonTests luacpp_test)
