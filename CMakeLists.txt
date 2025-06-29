cmake_minimum_required(VERSION 3.31)
project(DungeonArcheology
        DESCRIPTION "You're a researcher who locked yourself in an underground lab to study ancient crystals"
        VERSION 1.0
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

## Configure project source and headers
file(GLOB_RECURSE PROJECT_SRC ${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/precompile.hpp)

## Copy files to build
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})

## Add SFML to project
include(FetchContent)
FetchContent_Declare(sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(sfml)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

## Add toml++ to project
FetchContent_Declare(tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)
target_link_libraries(${PROJECT_NAME} PUBLIC tomlplusplus::tomlplusplus)