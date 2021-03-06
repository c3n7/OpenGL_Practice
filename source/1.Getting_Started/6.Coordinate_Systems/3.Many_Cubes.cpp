#include <GLFW/glfw3.h>
#include <find_resource.h>
#include <glad/glad.h>
#include <shader.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int screenWidth = 800;
int screenHeight = 600;

#if defined(__GNUC__) || defined(__GNUG__)
void framebuffer_size_callback(
        __attribute__((unused)) GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
#elif defined(_MSC_VER)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    screenWidth = height;
    screenHeight = height;
    glViewport(0, 0, width, height);
}
#endif

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// clang-format off
float vertices[] = {
    // positions          // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};
// clang-format on

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

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Copy our vertices array to a buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set the vertex VAO
    glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set the textures VAO
    glVertexAttribPointer(1,
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    unsigned int textures[2];
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    Resources resources;
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

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Load and generate the texture
    data = stbi_load(
            resources.getResourcePath("/textures/awesomeface.png").c_str(),
            &width,
            &height,
            &nrChannels,
            0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data);
    } else {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data);

    std::string vertex = resources.getShaderPath(
            "/1.Getting_Started/6.Coordinate_Systems/2.vertex.glsl");
    std::string fragment = resources.getShaderPath(
            "/1.Getting_Started/6.Coordinate_Systems/1.fragment.glsl");

    Shader ourShader(vertex.c_str(), fragment.c_str());
    ourShader.use();

    glUniform1i(glGetUniformLocation(ourShader.programID, "ourTexture1"), 0);
    ourShader.setInt("ourTexture2", 1);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Draw
        glClearColor(0.102f, 0.110f, 0.118f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f),
                (float)screenWidth / (float)screenHeight,
                0.1f,
                100.0f);

        unsigned int modelLoc =
                glGetUniformLocation(ourShader.programID, "model");
        unsigned int viewLoc =
                glGetUniformLocation(ourShader.programID, "view");
        unsigned int projectionLoc =
                glGetUniformLocation(ourShader.programID, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(
                projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i == 0 ? 3 : i);

            model = glm::rotate(model,
                    (float)glfwGetTime() * glm::radians(angle),
                    glm::vec3(1.0f, 0.3f, 0.5f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        // Check and call events and swap the buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, textures);

    glfwTerminate();
    return 0;
}
