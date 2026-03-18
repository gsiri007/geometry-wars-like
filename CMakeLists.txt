cmake_minimum_required(VERSION 3.28)
project(geometry-wars LANGUAGES CXX)

# Persistent dependency directory and compilation database for clangd
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Copy compile_commands.json to the root for clangd
add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json to root"
)

set(SOURCES
    main.cpp
    Vec2.cpp
    Entity.cpp
    EntityManager.cpp
    Game.cpp
)

add_executable(geometry-wars ${SOURCES})
target_compile_features(geometry-wars PRIVATE cxx_std_20)
target_link_libraries(geometry-wars PRIVATE SFML::Graphics SFML::Window SFML::System)

# Copy config files and fonts to build directory
file(COPY config.txt config.scheme.txt fonts DESTINATION ${CMAKE_BINARY_DIR})

