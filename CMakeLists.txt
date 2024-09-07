cmake_minimum_required (VERSION 3.8)

project ("MinecraftClone")
set(CMAKE_CXX_STANDARD 17)

# Libraries
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_MakeAvailable(glfw)
add_subdirectory("third-party/glad")


add_executable(
        ${CMAKE_PROJECT_NAME}
        "src/Engine.cpp" "include/Engine.hpp"
        "src/Shader.cpp" "include/Shader.hpp"
        "src/Renderer.cpp" "include/Renderer.hpp"
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include ${glad_SOURCE_DIR}/include)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw opengl32 glad)

# Copy resources to executable directory
add_custom_target(copy_resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_dependencies(${CMAKE_PROJECT_NAME} copy_resources)