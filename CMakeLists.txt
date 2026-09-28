cmake_minimum_required(VERSION 3.20)
project(Renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disables compiler-specific extensions for clean C++17

# 1. Collect all header and source files explicitly (recommended over GLOB)
set(SOURCES
    src/Main.cpp
    src/EBO.cpp
    src/Matrix.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/Mesh.cpp
    src/glad.c
    src/stb.cpp
)

set(HEADERS
    include/Main.h
    include/EBO.h
    include/Matrix.h
    include/Shader.h
    include/Texture.h
    include/VAO.h
    include/VBO.h
    include/Mesh.h
    GL/include/glad/glad.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(GL/glfw3)

# 2. Create the executable target with all source files
add_executable(Renderer ${SOURCES} ${HEADERS})

# 3. Tell the compiler where to find your header files (.hpp/.h)
target_include_directories(Renderer PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/GL/include
)

if(WIN32)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/GL/lib/glfw3.lib)
else()
    target_link_libraries(Renderer PRIVATE glfw ${CMAKE_DL_LIBS})
endif()

target_compile_features(Renderer PRIVATE cxx_std_17)

# 4. Automatically copy the 'Assets' folder to the build/bin directory after compilation
add_custom_command(TARGET Renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    $<TARGET_FILE_DIR:Renderer>/Assets
    COMMENT "Copying assets to output directory"
)

add_custom_command(TARGET Renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
    $<TARGET_FILE_DIR:Renderer>/Shaders
    COMMENT "Copying shaders to output directory"
)
