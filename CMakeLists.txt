cmake_minimum_required(VERSION 3.20)
project(particles VERSION 1.0)

# Generate complie commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specifying the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_VENDORED "Use vendored libraries" ON)

if (USE_VENDORED)
  add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
  add_subdirectory(vendored/glm EXCLUDE_FROM_ALL)
else()
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
  find_package(glm REQUIRED)
endif()

# Pass project directory as a compiler definition
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

# Find OpenGL Package
find_package(OpenGL REQUIRED)

include_directories(include ${OpenGL_INCLUDE_DIRS})

add_executable(particles
  src/app.cc
  src/Shader.cc
  src/Particle.cc
  src/Container.cc
  src/glad.c
)

# Link SDL3 and OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glm::glm ${OpenGL_LIBRARIES})
