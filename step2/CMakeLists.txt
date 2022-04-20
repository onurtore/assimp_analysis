cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Find the ignition-common library
find_package(ignition-common5 QUIET REQUIRED COMPONENTS events profiler)
find_package(ignition-math7)
find_package(assimp)
set(IGN_COMMON_VER ${ignition-common5_VERSION_MAJOR})

add_executable(mesh mesh.cc)
target_link_libraries(mesh ignition-common${IGN_COMMON_VER}::core)
target_link_libraries(mesh ignition-math7)
target_link_libraries(mesh assimp)



