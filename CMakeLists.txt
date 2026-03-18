cmake_minimum_required(VERSION 3.28)
project(geometry-wars LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

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

