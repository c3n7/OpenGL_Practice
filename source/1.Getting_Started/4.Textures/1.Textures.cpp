#include <GLFW/glfw3.h>
#include <find_resource.h>
#include <glad/glad.h>
#include <shader.h>
#include <stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
        // positions               // colors            // texture coords
        0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,    0.0f, 1.0f, // top left
};

unsigned int indices[] = {0, 1, 3, 1, 2, 3};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window =
            glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
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
    glViewport(0, 0, 800, 600);

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
    std::string vertex = resources.getShaderPath(
            "/1.Getting_Started/4.Textures/1.vertex.glsl");
    std::string fragment = resources.getShaderPath(
            "/1.Getting_Started/4.Textures/1.fragment.glsl");

    Shader ourShader(vertex.c_str(), fragment.c_str());

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(
            resources.getResourcePath("/textures/container.jpg").c_str(),
            &width,
            &height,
            &nrChannels,
            0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

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
