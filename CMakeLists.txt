cmake_minimum_required(VERSION 3.8)
project(frdm_fan_controller_driver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(frdm_fan_controller_driver ${SOURCE_FILES})
find_library(HID_API_LIB hidapi-libusb)
message(STATUS "HID Api library: ${HID_API_LIB}")
target_link_libraries(frdm_fan_controller_driver ${HID_API_LIB} pthread)
target_compile_options(frdm_fan_controller_driver PUBLIC "-Og")