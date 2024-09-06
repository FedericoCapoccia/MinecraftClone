cmake_minimum_required (VERSION 3.8)

project ("MinecraftVulkan")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory ("Engine")

# Libraries
add_subdirectory("thirdparty/glfw")