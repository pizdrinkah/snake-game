cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
project(snake VERSION 1.1 LANGUAGES CXX C)


add_library(interface STATIC src/interface.cpp include/interface.hpp)
target_include_directories(interface PUBLIC header src)
target_compile_features(interface PUBLIC cxx_std_23)


add_executable(snake src/main.cpp)
target_link_libraries(snake PUBLIC ncurses interface)