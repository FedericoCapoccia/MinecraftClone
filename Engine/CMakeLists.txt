project(Engine)
add_executable(Engine)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
target_sources(Engine PRIVATE ${MY_SOURCES})

target_include_directories(Engine PUBLIC include ${glad_SOURCE_DIR}/include)
target_link_libraries(Engine PUBLIC glfw opengl32 glad)

#file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR}/Game)