#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
	glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if(window == NULL)
    {
	std::cout << "Failed to create a GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, 800, 600);

    // First triangle
    float verticesTriangle1[] = {
	-0.9f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.45f, 0.5f, 0.0f,
    };

    // Second triangle
    float verticesTriangle2[] = {
	0.0f, -0.5f, 0.0f,
	0.9f, -0.5f, 0.0f,
	0.45f, 0.5f, 0.0f
    };

    const char* vertex_shader_source = "#version 330 core\n"
       "layout (location = 0) in vec3 aPos;\n"
       "\n"
       "void main()\n"
       "{\n"
       "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
       "}\n";

    const char* fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n";

    const char* fragment_shader_source_yellow = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n";


    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // Bind the VAO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // Copy our vertices in a buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle1), verticesTriangle1, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

    // Bind the VAO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    // Copy our vertices in a buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0);

    // Compile the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);
    // Check if compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION:FAILED\n" << infoLog << std::endl;
    }

    // Compile the fragment shader
    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragment_shader_source, NULL);
    glShaderSource(fragmentShader[1], 1, &fragment_shader_source_yellow, NULL);
    glCompileShader(fragmentShader[0]);
    glCompileShader(fragmentShader[1]);
    // Check if compilation was successful
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if(!success)
    {
	glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION:FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if(!success)
    {
	glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION:FAILED\n" << infoLog << std::endl;
    }

    // Create a shader program
    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    shaderProgram[1] = glCreateProgram();
    // Attach the shaders and link them
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    glLinkProgram(shaderProgram[0]);
    // Check if the linking was successful
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if(!success)
    {
	glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader[1]);
    glLinkProgram(shaderProgram[1]);
    // Check if the linking was successful
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if(!success)
    {
	glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
    }

    // Delete the shader objects as we no longer need them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);
    glDeleteShader(fragmentShader[1]);

    while(!glfwWindowShouldClose(window))
    {
	processInput(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram[0]);
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(shaderProgram[1]);
	glBindVertexArray(VAOs[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwPollEvents();
	glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
