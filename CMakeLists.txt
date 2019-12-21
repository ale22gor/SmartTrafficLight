cmake_minimum_required(VERSION 3.5)

project(SmartTrafficLight LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

find_package( OpenCV REQUIRED )
#find_package( Threads )

include_directories( ${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/*.h")

add_executable(SmartTrafficLight ${SOURCES})

target_link_libraries( SmartTrafficLight ${OpenCV_LIBS}) #${CMAKE_THREAD_LIBS_INIT} )









