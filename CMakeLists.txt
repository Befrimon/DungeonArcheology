cmake_minimum_required(VERSION 3.31)
project(DungeonArcheology
        DESCRIPTION "You're a researcher who locked yourself in an underground lab to study ancient crystals"
        VERSION 0.1
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

## Configure project source and headers
file(GLOB PROJECT_SRC ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB PRECOMPILE  ${PROJECT_SOURCE_DIR}/precompile/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PRECOMPILE})

## Copy files to build
file(COPY ${PROJECT_SOURCE_DIR}/textures DESTINATION ${PROJECT_BINARY_DIR})

## Add SFML to project
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0 GIT_SHALLOW ON
        EXCLUDE_FROM_ALL  SYSTEM
)
FetchContent_MakeAvailable(SFML)
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        SFML::System SFML::Window SFML::Graphics
)