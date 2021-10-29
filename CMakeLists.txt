cmake_minimum_required(VERSION 3.16)
project("TGJGE")

#BASICALLY RELEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_CXX_FLAGS "-g -ggdb -fsanitize=address")
SET(CMAKE_CXX_FLAGS "-g")

#PROFILERMODE
#SET(CMAKE_CXX_FLAGS "-g -pg")

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(SDL2_ttf SDL2_ttf)
find_library(GLEW GLEW)
find_library(GL GL)


#creating the library
include_directories(src/)
include_directories(vendor/stb/)
file(GLOB_RECURSE "engine" SRC src/*.c)
add_library(tgjge STATIC ${engine})

target_link_libraries(tgjge LINK_PRIVATE "${SDL2}")
target_link_libraries(tgjge LINK_PRIVATE "${SDL2_ttf}")
target_link_libraries(tgjge LINK_PRIVATE m)
target_link_libraries(tgjge LINK_PRIVATE "${GLEW}")
target_link_libraries(tgjge LINK_PRIVATE "${GL}")

#creating library test
file(GLOB_RECURSE "test" SRC test.c)
add_executable(test ${test})
target_link_libraries(test LINK_PRIVATE tgjge)
file(COPY shaders DESTINATION .)
file(COPY assets DESTINATION .)

#creating TGE (T3V's Game Jam Game Engine Editor)
file(GLOB_RECURSE "tge" SRC TGE/*.cpp)
add_executable(tge ${tge})
target_link_libraries(tge LINK_PRIVATE tgjge)
file(COPY shaders DESTINATION TGE/.)
file(COPY TGE/assets DESTINATION TGE/.)