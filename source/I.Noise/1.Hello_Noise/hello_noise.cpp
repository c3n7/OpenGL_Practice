#include <FastNoise.h>
#include <GLFW/glfw3.h>
#include <find_resource.h>
#include <glad/glad.h>
#include <shader.h>

#include <iostream>

void framebuffer_size_callback(
        __attribute__((unused)) GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// clang-format off
float vertices[] = {
    // positions               // colors            // texture coords
    0.9f, 0.9f, 0.0f,       1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
    0.9f, -0.9f, 0.0f,      0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
    -0.9f, -0.9f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
    -0.9f, 0.9f, 0.0f,      1.0f, 1.0f, 0.0f,    0.0f, 1.0f, // top left
};
// clang-format on

unsigned int indices[] = {0, 1, 3, 1, 2, 3};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window =
            glfwCreateWindow(800, 800, "Hello Triangle", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 800);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Copy our vertices array to a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Copy our indices to the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Set the vertex VAO
    glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set the colors VAO
    glVertexAttribPointer(1,
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set the textures VAO
    glVertexAttribPointer(2,
            2,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    Resources resources;
    std::string vertex =
            resources.getShaderPath("/I.Noise/1.Hello_Noise/vertex.glsl");
    std::string fragment =
            resources.getShaderPath("/I.Noise/1.Hello_Noise/fragment.glsl");

    Shader ourShader(vertex.c_str(), fragment.c_str());

    FastNoise myNoise;                       // Create a FastNoise object
    myNoise.SetNoiseType(FastNoise::Perlin); // Set the desired noise type
    myNoise.SetFrequency(0.02f);
    // myNoise.SetCellularDistanceFunction(FastNoise::Natural);
    myNoise.SetSeed(3455);

    int mapWidth = 1024;
    float* heightMap =
            new float[mapWidth * mapWidth]; // 2D heightmap to create terrain
    std::cout << mapWidth << std::endl;

    GLubyte* texData = new GLubyte[mapWidth * mapWidth * 3];

    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapWidth; y++) {
            // One dimension index
            int i = ((x)*mapWidth) + y;
            heightMap[i] = myNoise.GetNoise((float)x, (float)y);
        }
    }

    float max = 0.0f;
    float min = 2.0f;

    for (int i = 0; i < mapWidth * mapWidth; i++) {
        if (heightMap[i] > max) {
            max = heightMap[i];
        }
        if (heightMap[i] < min) {
            min = heightMap[i];
        }
    }

    float m = 1 / (max - min);
    float c1 = 0 - (m * min);
    float c2 = 0 - (m * min);

    std::cout << "\nMinimax Before\n";
    std::cout << "\tMax: " << max << std::endl;
    std::cout << "\tMin: " << min << std::endl;

    if (c1 != c2) {
        std::cout << "Ummm, help?" << std::endl;
    }

    max = 0.0f;
    min = 2.0f;

    for (int i = 0; i < mapWidth * mapWidth; i++) {
        // std::cout << std::endl;
        heightMap[i] = (m * heightMap[i]) + c1;
        if (heightMap[i] > max) {
            max = heightMap[i];
        }
        if (heightMap[i] < min) {
            min = heightMap[i];
        }

            // y = 3x;
        int colorIndex = (3 * i);
        GLubyte colorVal = (GLubyte)(255 * heightMap[i]);
        texData[colorIndex] = colorVal;
        texData[colorIndex + 1] = colorVal;
        texData[colorIndex + 2] = colorVal;
    }

    std::cout << "\nMinimax After\n";
    std::cout << "\tMax: " << max << std::endl;
    std::cout << "\tMin: " << min << std::endl;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float color[] = {1, 1, 1, 1};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    std::cout << (int)texData[0] << " " << (int)texData[1] << " "
              << (int)texData[2] << std::endl;
    std::cout << (int)texData[765] << " " << (int)texData[766] << " "
              << (int)texData[767] << std::endl;

    // Pass the noise
    glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            mapWidth,
            mapWidth,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            texData);

    delete[] heightMap;
    delete[] texData;

    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Draw
        glClearColor(0.102f, 0.110f, 0.118f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Check and call events and swap the buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);

    glfwTerminate();
    return 0;
}
