cmake_minimum_required(VERSION 3.27)
project(BugLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(BugLife main.cpp
        Creeper.cpp
        Board.cpp
        Hopper.cpp
        Crawler.cpp
        Bug.cpp
        Super.cpp
)

#include(FetchContent)
#set(BUILD_SHARED_LIBS OFF)
#FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
#FetchContent_MakeAvailable(SFML)
#target_link_libraries(BugLife sfmlRunSimulation-graphics)

# https://youtu.be/4oh-tmxtIrA?t=953
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

#https://youtu.be/4oh-tmxtIrA?t=1134
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)

#https://youtu.be/4oh-tmxtIrA?t=1282
target_link_libraries(BugLife sfml-system sfml-window sfml-graphics sfml-audio)