cmake_minimum_required (VERSION 3.8)

project ("MinecraftVulkan")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory ("Engine")
include(FetchContent)

FetchContent_Declare(glm GIT_REPOSITORY	https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

find_package(Vulkan REQUIRED)