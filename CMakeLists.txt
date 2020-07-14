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

    if(MSVC)
        target_compile_options(${PROJ_NAME} PRIVATE /W4 /WX)
    else()
        target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()

    target_link_libraries(${PROJ_NAME} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${PROJ_NAME} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${PROJ_NAME} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${PROJ_NAME} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${PROJ_NAME} "glad" "${CMAKE_DL_LIBS}")
endFunction()

set(tobuildshaderless_sources
    "${SRC_DIR}/1.Getting_Started/1.Hello_Window.cpp"
    "${SRC_DIR}/1.Getting_Started/2.0.Hello_Triangle.cpp"
    "${SRC_DIR}/1.Getting_Started/2.1.Hello_Rectangle.cpp"
    "${SRC_DIR}/1.Getting_Started/2.2.Exercise_Qn1.cpp"
    "${SRC_DIR}/1.Getting_Started/2.3.Exercise_Qn2.cpp"
    "${SRC_DIR}/1.Getting_Started/2.4.Exercise_Qn3.cpp"
)

set(tobuildshaderless_targets
    "1.Hello_Window"
    "2.0.Hello_Triangle"
    "2.1.Hello_Rectangle"
    "2.2.Exercise_Qn1"
    "2.3.Exercise_Qn2"
    "2.4.Exercise_Qn3"
)

foreach(source target IN ZIP_LISTS  tobuildshaderless_sources tobuildshaderless_targets)
    buildFile(${source} ${target})
endforeach()

# =============================================================================
#                                 Shaders
# =============================================================================
# Red Triangle
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/1.Red_Triangle_Ex1.cpp")
set(TARGET_NM "3.1.Red_Triangle_Ex1")
buildFile(${SOURCES} ${TARGET_NM})

# Green to Black Triangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/2.Green_To_Black_Ex2.cpp")
set(TARGET_NM "3.2.Green_To_Black_Ex2")
buildFile(${SOURCES} ${TARGET_NM})

# Colorful Triangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/3.Colorful_Triangle_Ex3.cpp")
set(TARGET_NM "3.3.Colorful_Triangle_Ex3")
buildFile(${SOURCES} ${TARGET_NM})

# shader
set(SHADER_DIR "${LIB_DIR}/shader")
add_library("shader" "${SHADER_DIR}/shader.cpp")
target_include_directories("shader" PRIVATE "${SHADER_DIR}" "${GLAD_DIR}/include")

# find_resource
set(FR_DIR "${LIB_DIR}/find_resource")
set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(PROJECT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source")
configure_file (
    "${FR_DIR}/find_resource.h"
    "${CMAKE_CURRENT_BINARY_DIR}/libraries/find_resource/find_resource.h" @ONLY
)
configure_file (
    "${FR_DIR}/find_resource.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/libraries/find_resource/find_resource.cpp" @ONLY
)

set(FR_DIR "${CMAKE_CURRENT_BINARY_DIR}/libraries/find_resource")
add_library("find_resource" "${FR_DIR}/find_resource.cpp")
target_include_directories("find_resource" PRIVATE "${LIB_DIR}")


function(buildFileWithShader)
    list(GET ARGV 0 SRCS)
    list(GET ARGV 1 PROJ_NAME)

    # Executable definition and properties
    add_executable(${PROJ_NAME} ${SRCS})
    target_include_directories(${PROJ_NAME} PRIVATE "${SRC_DIR}")
    set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 11)

    if(MSVC)
        target_compile_options(${PROJ_NAME} PRIVATE /W4 /WX)
    else()
        target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()

    target_link_libraries(${PROJ_NAME} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${PROJ_NAME} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${PROJ_NAME} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${PROJ_NAME} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${PROJ_NAME} "glad" "${CMAKE_DL_LIBS}")

    target_include_directories(${PROJ_NAME} PRIVATE "${SHADER_DIR}")
    target_link_libraries(${PROJ_NAME} "shader")

    target_include_directories(${TARGET_NM} PRIVATE "${FR_DIR}")
    target_link_libraries(${TARGET_NM} "find_resource")
endFunction()

# Shaders Exercise_Qn1
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/4.Exercise_Qn1.cpp")
set(TARGET_NM "3.4.Exercise_Qn1")
buildFileWithShader(${SOURCES} ${TARGET_NM} ${STAGE_NM} ${V_PATH} ${F_PATH})

# Shaders Exercise_Qn2
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/5.Exercise_Qn2.cpp")
set(TARGET_NM "3.5.Exercise_Qn2")
buildFileWithShader(${SOURCES} ${TARGET_NM} ${STAGE_NM} ${V_PATH} ${F_PATH})

# Shaders Exercise_Qn3
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/3.Shaders/6.Exercise_Qn3.cpp")
set(TARGET_NM "3.6.Exercise_Qn3")
buildFileWithShader(${SOURCES} ${TARGET_NM} ${STAGE_NM} ${V_PATH} ${F_PATH})


# stb_image
set(STB_DIR "${LIB_DIR}/stb_image")
add_library("stb_image" "${STB_DIR}/stb_image.cpp")
target_include_directories("stb_image" PRIVATE "${STB_DIR}")


# ======================================================================================

function(buildFileWithTexture)
    list(GET ARGV 0 SRCS)
    list(GET ARGV 1 TARGET_NM)

    # set(SRCS "${CMAKE_CURRENT_BINARY_DIR}/src/${STAGE_NM}/${PROJ_NAME}.cpp")

    # Executable definition and properties
    add_executable(${TARGET_NM} ${SRCS})
    target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
    set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

    if(MSVC)
        target_compile_options(${TARGET_NM} PRIVATE /W4 /WX)
    else()
        target_compile_options(${TARGET_NM} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()

    target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

    target_include_directories(${TARGET_NM} PRIVATE "${SHADER_DIR}")
    target_link_libraries(${TARGET_NM} "shader")

    target_include_directories(${TARGET_NM} PRIVATE "${STB_DIR}")
    target_link_libraries(${TARGET_NM} "stb_image")

    target_include_directories(${TARGET_NM} PRIVATE "${FR_DIR}")
    target_link_libraries(${TARGET_NM} "find_resource")
endFunction()

# 4. TEXTURES
# Textured Colorful Rectangle
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/4.Textures/1.Textures.cpp")
set(TARGET_NM "4.1.Textures")
buildFileWithTexture(${SOURCES} ${TARGET_NM})

# Texture Units
# Source files
set(SOURCES "${SRC_DIR}/1.Getting_Started/4.Textures/2.Texture_Units.cpp")
set(TARGET_NM "4.2.Texture_Units")
buildFileWithTexture(${SOURCES} ${TARGET_NM})


# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================
#                                        GLM
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================

set(GLM_INCLUDE_DIR "${LIB_DIR}/glm")

function(buildFileWithGLM)
    list(GET ARGV 0 SRCS)
    list(GET ARGV 1 TARGET_NM)

    # set(SRCS "${CMAKE_CURRENT_BINARY_DIR}/src/${STAGE_NM}/${PROJ_NAME}.cpp")

    # Executable definition and properties
    add_executable(${TARGET_NM} ${SRCS})
    target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
    set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)
 
    if(MSVC)
        # target_compile_options(${TARGET_NM} PRIVATE /W4 /WX)
        target_compile_options(${TARGET_NM} PRIVATE /W4)
    else()
        target_compile_options(${TARGET_NM} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()

    target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

    target_include_directories(${TARGET_NM} PRIVATE "${SHADER_DIR}")
    target_link_libraries(${TARGET_NM} "shader")

    target_include_directories(${TARGET_NM} PRIVATE "${STB_DIR}")
    target_link_libraries(${TARGET_NM} "stb_image")

    target_include_directories(${TARGET_NM} PRIVATE "${FR_DIR}")
    target_link_libraries(${TARGET_NM} "find_resource")

    # glm
    target_include_directories(${TARGET_NM} PRIVATE ${GLM_INCLUDE_DIR})
endFunction()

set(tobuildwithglm_sources
    "${SRC_DIR}/1.Getting_Started/5.Transformations/1.Transformations.cpp"
    "${SRC_DIR}/1.Getting_Started/5.Transformations/2.Rotation.cpp"
    "${SRC_DIR}/1.Getting_Started/6.Coordinate_Systems/1.Hello_Coordinates.cpp"
    "${SRC_DIR}/1.Getting_Started/6.Coordinate_Systems/2.One_Cube.cpp"
    "${SRC_DIR}/1.Getting_Started/6.Coordinate_Systems/3.Many_Cubes.cpp"
)

set(tobuildwithglm_targets
    "5.1.Transformations"
    "5.2.RotatedRect"
    "5.3.Hello_Coordinates"
    "5.4.One_Cube"
    "5.5.Many_Cubes"
)

foreach(source target IN ZIP_LISTS  tobuildwithglm_sources tobuildwithglm_targets)
    buildFileWithGLM(${source} ${target})
endforeach()

# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================
#                                    NOISE
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================

set(GLM_INCLUDE_DIR "${LIB_DIR}/glm/")

set(FASTNOISE_DIR "${LIB_DIR}/fastnoise")
add_library("fastnoise" "${FASTNOISE_DIR}/FastNoise.cpp")
target_include_directories("fastnoise" PRIVATE "${LIB_DIR}")

# imgui
set(IMGUI "${LIB_DIR}/imgui/imgui.cpp")
set(IMGUI_DIR "${LIB_DIR}/imgui")
set(IMGUI_DRAW "${LIB_DIR}/imgui/imgui_draw.cpp")
set(IMGUI_DEMO "${LIB_DIR}/imgui/imgui_demo.cpp")
set(IMGUI_WIDGETS "${LIB_DIR}/imgui/imgui_widgets.cpp")

# OpenGL 3 implementation
set(IMGUI_IMPL_GL3 "${LIB_DIR}/imgui/examples/imgui_impl_opengl3.cpp")

# GLFW Implementation
set(IMGUI_IMPL_GLFW "${LIB_DIR}/imgui/examples/imgui_impl_glfw.cpp")

function(buildFileWithNoise)
    list(GET ARGV 0 SRCS)
    list(GET ARGV 1 TARGET_NM)
    list(GET ARGV 2 USE_NOISE)
    list(GET ARGV 3 USE_IMGUI)

    # set(SRCS "${CMAKE_CURRENT_BINARY_DIR}/src/${STAGE_NM}/${PROJ_NAME}.cpp")

    # Executable definition and properties
    add_executable(${TARGET_NM} ${SRCS})
    target_include_directories(${TARGET_NM} PRIVATE "${SRC_DIR}")
    set_property(TARGET ${TARGET_NM} PROPERTY CXX_STANDARD 11)

    if(MSVC)
        # Go easy on GLM and IMGUI
        # target_compile_options(${TARGET_NM} PRIVATE /W4 /WX)
        if(${USE_IMGUI} OR ${USE_NOISE})
            target_compile_options(${TARGET_NM} PRIVATE /W4)
        else()
            target_compile_options(${TARGET_NM} PRIVATE /W4)
        endif()
    else()
        if(${USE_IMGUI} OR ${USE_NOISE})
            target_compile_options(${TARGET_NM} PRIVATE 
                -Wall -Wextra -Wconversion -pedantic)
        else()
            target_compile_options(${TARGET_NM} PRIVATE 
                -Wall -Wextra -Wconversion -pedantic -Werror)
        endif()
    endif()
 

    target_link_libraries(${TARGET_NM} "glfw" "${GLFW_LIBRARIES}")
    target_include_directories(${TARGET_NM} PRIVATE "${GLFW_DIR}/include")
    target_compile_definitions(${TARGET_NM} PRIVATE "GLFW_INCLUDE_NONE")

    target_include_directories(${TARGET_NM} PRIVATE "${GLAD_DIR}/include")
    target_link_libraries(${TARGET_NM} "glad" "${CMAKE_DL_LIBS}")

    target_include_directories(${TARGET_NM} PRIVATE "${SHADER_DIR}")
    target_link_libraries(${TARGET_NM} "shader")

    target_include_directories(${TARGET_NM} PRIVATE "${STB_DIR}")
    target_link_libraries(${TARGET_NM} "stb_image")

    target_include_directories(${TARGET_NM} PRIVATE "${FR_DIR}")
    target_link_libraries(${TARGET_NM} "find_resource")

    # glm
    target_include_directories(${TARGET_NM} PRIVATE ${GLM_INCLUDE_DIR})

    if(${USE_NOISE})
        # fastnoise
        target_link_libraries(${TARGET_NM} "fastnoise")
        target_include_directories(${TARGET_NM} PRIVATE ${FASTNOISE_DIR})
    endif()

    if(${USE_IMGUI})
        # target_link_libraries(${TARGET_NM} "imgui")
        target_include_directories(${TARGET_NM} PRIVATE ${IMGUI_DIR})
        target_include_directories(${TARGET_NM} PRIVATE "${IMGUI_DIR}/examples")
        target_compile_definitions(${TARGET_NM} PRIVATE "IMGUI_IMPL_OPENGL_LOADER_GLAD")
        target_sources(${TARGET_NM} PRIVATE ${IMGUI_IMPL_GLFW})
        target_sources(${TARGET_NM} PRIVATE ${IMGUI_IMPL_GL3})
        target_sources(${TARGET_NM} PRIVATE ${IMGUI})
        target_sources(${TARGET_NM} PRIVATE ${IMGUI_DRAW})
        target_sources(${TARGET_NM} PRIVATE ${IMGUI_DEMO})
        target_sources(${TARGET_NM} PRIVATE ${IMGUI_WIDGETS})
    endif()
endFunction()

# 1. Hello Noise
set(SOURCES "${SRC_DIR}/I.Noise/1.Hello_Noise/hello_noise.cpp")
set(TARGET_NM "I.1.Hello_Noise")
buildFileWithNoise(${SOURCES} ${TARGET_NM} TRUE FALSE)

# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================
#                                     Dear IMGUI
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
# ========================================================================================

# 1. Hello Imgui
set(SOURCES "${SRC_DIR}/II.imGUI/1.Hello_imGUI/main.cpp")
set(TARGET_NM "II.1.Hello_imGUI")
buildFileWithNoise(${SOURCES} ${TARGET_NM} TRUE TRUE)


