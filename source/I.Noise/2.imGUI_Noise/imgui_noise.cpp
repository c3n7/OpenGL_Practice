#include <FastNoise.h>
#include <GLFW/glfw3.h>
#include <find_resource.h>
#include <glad/glad.h>
#include <shader.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#if defined(__GNUC__) || defined(__GNUG__)
void framebuffer_size_callback(
        __attribute__((unused)) GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
#elif defined(_MSC_VER)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}
#endif

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int mapWidth = 1024;
GLubyte* texData = new GLubyte[mapWidth * mapWidth * 3];
FastNoise myNoise; // Create a FastNoise object

void generateNoiseTexture(float frequency, FastNoise::NoiseType noiseType) {
    myNoise.SetNoiseType(noiseType); // Set the desired noise type
    myNoise.SetFrequency(frequency);
    // myNoise.SetCellularDistanceFunction(FastNoise::Natural);

    float* heightMap =
            new float[mapWidth * mapWidth]; // 2D heightmap to create terrain

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

    delete[] heightMap;
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

    // generateNoiseTexture(0.02f, FastNoise::Perlin);
    generateNoiseTexture(0.02f, (FastNoise::NoiseType)2);

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontFromFileTTF(
            resources.getResourcePath("/fonts/Roboto-Medium.ttf").c_str(),
            16.0f);
    io.Fonts->AddFontFromFileTTF(
            resources.getResourcePath("/fonts/DroidSans.ttf").c_str(), 16.0f);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.102f, 0.110f, 0.118f, 1.0f);

    const char* noises[] = {"Value",
            "Value Fractal",
            "Perlin",
            "Perlin Fractal",
            "Simplex",
            "Simplex Fractal",
            "Cellular",
            "White Noise",
            "Cubic",
            "Cubic Fractal"};

    float last_f = 0.0f;

    static int previous_noise_type = 2, current_noise_type = 2;
    static int previous_seed = 0, current_seed = 0;

    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        static float f = 0.02f;

        if (f != last_f || previous_noise_type != current_noise_type ||
                current_seed != previous_seed) {
            myNoise.SetSeed(current_seed);

            generateNoiseTexture(f, (FastNoise::NoiseType)current_noise_type);

            std::cout << "Last Noise: " << previous_noise_type << " "
                      << noises[previous_noise_type]
                      << "\tCurrent Noise: " << current_noise_type << " "
                      << noises[current_noise_type] << std::endl;

            last_f = f;
            previous_noise_type = current_noise_type;
            previous_seed = current_seed;

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
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window
        // (Most of the sample code is in ImGui::ShowDemoWindow()!
        // You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        // ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves.
        // We use a Begin/End pair to created a named window.
        {
            // Create a window called "Hello, world!" and append into it.
            ImGui::Begin("Noise Settings");

            // Display some text (you can use a format strings too)
            ImGui::Text("General");

            // Edit bools storing our window open/close state
            // ImGui::Checkbox("Demo Window", &show_demo_window);
            // ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("Frequency",
                    &f,
                    0.02f,
                    1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

            ImGui::Combo("Noise Type",
                    &current_noise_type,
                    "Value\0Value Fractal"
                    "\0Perlin\0Perlin Fractal"
                    "\0Simplex\0Simplex Fractal"
                    "\0Cellular\0White Noise"
                    "\0Cubic\0Cubic Fractal\0\0");

            ImGui::InputInt("Seed", &current_seed);

            // Buttons return true when clicked (most widgets return true when edited/activated)
            if (ImGui::Button("Random Seed"))
                current_seed = rand();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
            // Pass a pointer to our bool variable
            // (the window will have a closing button that will clear the bool when clicked)
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Draw
        ImGui::Render();
        glClearColor(
                clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Check and call events and swap the buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] texData;
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);

    glfwTerminate();
    return 0;
}
