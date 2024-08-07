cmake_minimum_required(VERSION 3.29)
project(v10 VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/binary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES "main.cpp" "src/*.cpp" "glad/*.c" )
set(GLAD_INCLUDE_DIRS "glad/")
set(GLM_INCLUDE_DIRS "glm/")
# "sources/headers/*.hpp"

add_executable(
    ${PROJECT_NAME}
    WIN32 ${SRC_FILES}
)
    # WIN32
find_package(glm CONFIG REQUIRED)
if (NOT glm_FOUND)
    message(FATAL_ERROR "GLM NOT FOUND")
endif()

find_package(SDL2 REQUIRED CONFIG COMPONENTS HINTS "C:/SDL2/x86_64-w64-mingw32/lib/cmake/SDL2/" )
if (NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 NOT FOUND")
endif()

find_package(OpenGL REQUIRED)
if (NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL NOT FOUND")
endif()

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${GLAD_INCLUDE_DIRS}
    PRIVATE ${SDL2_INCLUDE_DIRS}
    PRIVATE ${OpenGL_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    glm::glm
    ${OpenGL_LIBRARIES}
)

# v10:
#     g++ .\main.cpp -L C:\\Users\Vinii\Documents\VsCode\sdl2-compile-dir\src\lib -I C:\\Users\Vinii\Documents\VsCode\sdl2-compile-dir\src\include -lmingw32 -lSDL2main -lSDL2 -mwindows -o ./out/winBinary.exe
