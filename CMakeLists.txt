cmake_minimum_required(VERSION 3.10)
project(FEM3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0 
)

FetchContent_MakeAvailable(eigen)

include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)

set(SOURCES src/main.cpp src/FEM.cpp src/Mesh.cpp)

add_executable(app ${SOURCES})

target_link_libraries(app PRIVATE Eigen3::Eigen gmsh)