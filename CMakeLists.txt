# Project definition 
cmake_minimum_required(VERSION 3.12.4)
project(OpenGL_Practice)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")


function(buildFile)
    list(GET ARGV 0 SRCS)
    list(GET ARGV 1 PROJ_NAME)

    # Executable definition and properties
    add_executable(${PROJ_NAME} ${SRCS})
    target_include_directories(${PROJ_NAME} PRIVATE "${SRC_DIR}")
    set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 11)

    target_link_libraries(${PROJ_NAME} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${PROJ_NAME} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${PROJ_NAME} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${PROJ_NAME} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${PROJ_NAME} "glad" "${CMAKE_DL_LIBS}")
endFunction()

# Hello Window
set(SOURCES "${SRC_DIR}/1.Getting_Started/1.Hello_Window.cpp")
set(TARGET_NM "1.Hello_Window")
buildFile(${SOURCES} ${TARGET_NM})

# Hello Triangle
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.1.Hello_Triangle.cpp")
set(TARGET_NM "2.1.Hello_Triangle")
buildFile(${SOURCES} ${TARGET_NM})

# Hello Rectangle
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.2.Hello_Rectangle.cpp")
set(TARGET_NM "2.2.Hello_Rectangle")
buildFile(${SOURCES} ${TARGET_NM})

# Hello Triangle Exercise Qn 1
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.3.Exercise_Qn1.cpp")
set(TARGET_NM "2.3.Exercise_Qn1")
buildFile(${SOURCES} ${TARGET_NM})

# Hello Triangle Exercise Qn 2
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.4.Exercise_Qn2.cpp")
set(TARGET_NM "2.4.Exercise_Qn2")
buildFile(${SOURCES} ${TARGET_NM})

# Hello Triangle Exercise Qn 3
set(SOURCES "${SRC_DIR}/1.Getting_Started/2.5.Exercise_Qn3.cpp")
set(TARGET_NM "2.5.Exercise_Qn3")
buildFile(${SOURCES} ${TARGET_NM})


# Red Triangle
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.0.Red_Triangle_Ex1.cpp")
set(TARGET_NM "3.0.Red_Triangle_Ex1")
buildFile(${SOURCES} ${TARGET_NM})

# Green to Black Triangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.1.Green_To_Black_Ex2.cpp")
set(TARGET_NM "3.1.Green_To_Black_Ex2")
buildFile(${SOURCES} ${TARGET_NM})

# Colorful Triangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.2.Colorful_Triangle_Ex3.cpp")
set(TARGET_NM "3.2.Colorful_Triangle_Ex3")
buildFile(${SOURCES} ${TARGET_NM})
