cmake_minimum_required(VERSION 3.20)

# adding vcpkg to cmake
set(
    CMAKE_TOOLCHAIN_FILE
    "${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
)
set(VCPKG_BUILD ON)

# project settings
project(ogl LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# libraries from vcpkg
# opengl libs
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
# formatting library
find_package(fmt CONFIG REQUIRED)
# stb library
find_path(STB_INCLUDE_DIRS "stb.h")

set(
    project_lib_files
    # project library files goes here
    ${CMAKE_SOURCE_DIR}/include/utils/FileIO.cpp
    ${CMAKE_SOURCE_DIR}/include/ogl/Init.cpp
    ${CMAKE_SOURCE_DIR}/include/ogl/shaders/Shader.cpp
    ${CMAKE_SOURCE_DIR}/include/ogl/textures/Texture.cpp
)

# sources
set(
    project_source_files
    # source files go here
    ${CMAKE_SOURCE_DIR}/tutorial/main.cpp
    ${CMAKE_SOURCE_DIR}/tutorial/colorflash/colorflash.cpp
    ${CMAKE_SOURCE_DIR}/tutorial/triangle/triangle.cpp
    ${CMAKE_SOURCE_DIR}/tutorial/rectangle/rectangle.cpp
    ${CMAKE_SOURCE_DIR}/tutorial/rectangle/shadedRectangle.cpp
)

# executable
add_executable(${PROJECT_NAME} ${project_lib_files} ${project_source_files})

# link libraries
# opengl libs
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

if(WIN32) # windows
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL32)
else()   # unix...here's to hoping this works...
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)
endif()

# fmt lib
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)

# stb include
target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/)

# Copy assets to binary directory
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:ogl>/assets
)
