cmake_minimum_required(VERSION 3.16)
project(TravelTown LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(TravelTown ${SOURCES})

target_include_directories(TravelTown PRIVATE include)

# SFML 3 : majuscules sur les composants ET les targets
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(TravelTown SFML::Graphics SFML::Window SFML::System)

if(WIN32)
    add_custom_command(TARGET TravelTown POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/msys64/mingw64/bin"
        $<TARGET_FILE_DIR:TravelTown>)
endif()