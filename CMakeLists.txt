# Project definition 
cmake_minimum_required(VERSION 3.1)
project(OpenGL_Practice)

# Hello Window
# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/")
set(SOURCES "${SRC_DIR}/1.Getting_Started/1.Hello_Window.cpp")
set(TARGET_NM "1.Hello_Window")

# Executable definition and properties
add_executable(${TARGET_NM} ${SOURCES})
target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

# GLFW
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(GLFW_DIR "${LIB_DIR}/glfw-3.3")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

# Hello Triangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.Hello_Triangle.cpp")
set(TARGET_NM "2.Hello_Triangle")

# Executable definition and properties
add_executable(${TARGET_NM} ${SOURCES})
target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

# GLFW
target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

# glad
target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")


# Hello Rectangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.2.Hello_Rectangle.cpp")
set(TARGET_NM "2.2.Hello_Rectangle")

# Executable definition and properties
add_executable(${TARGET_NM} ${SOURCES})
target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

# GLFW
target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

# glad
target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

# Hello Triangle Exercise Qn 1
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.3.Exercise_Qn1.cpp")
set(TARGET_NM "2.3.Exercise_Qn1")

# Executable definition and properties
add_executable(${TARGET_NM} ${SOURCES})
target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

# GLFW
target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

# glad
target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

