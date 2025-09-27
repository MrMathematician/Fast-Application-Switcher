cmake_minimum_required(VERSION 3.10)
project(FastApplicationSwitcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/../include)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(X11 REQUIRED)
find_library(XI_LIB Xi REQUIRED)

# X11 specific stuff
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} ${XI_LIB})

# won't compile without the X11 headers!!!!!!
include_directories(${X11_INCLUDE_DIR})

