#if 0

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "stb_image.h"

static void InitGL();
static void processInput(GLFWwindow* window);
static GLuint CreateProgram(GLchar**, GLsizei, GLchar**, GLsizei);
static GLuint CreateShader(GLenum, GLchar**, GLsizei);

int main()
{
    InitGL();
    GLFWwindow* window = glfwCreateWindow(1280, 1280, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();

    // Shaders
    GLchar* vertex_shader_src =
        "#version 330 core\n"
        "in vec2 aPos;\n"
        "in vec2 tex_cord;\n"
        "out vec2 v_TexCord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0f);\n"
        "   v_TexCord = tex_cord;\n"
        "}\n";

    GLchar* fragment_shader_src = 
        "#version 330 core\n"
        "out vec4 color;\n"
        "in vec2 v_TexCord;\n"
        "\n"
        "uniform sampler2D u_TexSlot;\n"
        "void main()\n"
        "{\n"
        "   vec4 TexCol = texture(u_TexSlot, v_TexCord);\n"
        "   color = TexCol;\n"
        "}\n";
    GLuint shader = CreateProgram(&vertex_shader_src, 1, &fragment_shader_src, 1);
    glUseProgram(shader);
    // Uniform
    /*
    int location = glGetUniformLocation(shader, "u_Color");
    if (location == -1) return 0;
    glUniform4f(location, 0.3f, 0.7f, 1.0f, 1.0f);
    */
    
    // Uniform for texture slot
    int TexSlot_location = glGetUniformLocation(shader, "u_TexSlot");
    if (TexSlot_location == -1) return 1;
    glUniform1i(TexSlot_location, GL_TEXTURE0);
    
    // Buffers
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,//0
         0.5f, -0.5f, 1.0f, 0.0f,//1
         0.5f,  0.5f, 1.0f, 1.0f,//2
        -0.5f,  0.5f, 0.0f, 1.0f //3
    };
    unsigned int elements[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shader, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(shader, "tex_cord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    
    //glEnableVertexAttribArray(0);
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    //Textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    char filepath[] = "texturers/alph.png";
    //char filepath[] = "texturers/lion.png";
    unsigned char* LocBuf = NULL;
    GLuint texture_id;
    unsigned int slot = 0;
    int Width = 0, Hight = 0, BitsPerPix = 0;

    stbi_set_flip_vertically_on_load(1);
    LocBuf = stbi_load(filepath, &Width, &Hight, &BitsPerPix, 4);
    if (!LocBuf) return 0;

    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0 + slot); 
    glBindTexture(GL_TEXTURE_2D, texture_id); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocBuf);// ?
    //glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    stbi_image_free(LocBuf);
    
    

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shader);
        //glBindVertexArray(VAO);
       //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        //glUniform4f(location, 0.3f, 0.7f, 1.0f, 1.0f);
        //glUniform1i(TexSlot_location, GL_TEXTURE0 + slot);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteTextures(1, &texture_id);
    glDeleteProgram(shader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

static void InitGL()
{
    if (!glfwInit()) { exit(0); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
  
}
static GLuint CreateProgram(GLchar** vsh_src, GLsizei length_vsh, GLchar** fsh_src, GLsizei length_fsh)
{
    //Getting id'es of shaders and program
    GLuint program = glCreateProgram();
    GLuint vsh_id = CreateShader(GL_VERTEX_SHADER, vsh_src, length_vsh);
    GLuint fsh_id = CreateShader(GL_FRAGMENT_SHADER, fsh_src, length_fsh);

    //Doing things to link all
    glAttachShader(program, vsh_id);
    glAttachShader(program, fsh_id);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vsh_id);
    glDeleteShader(fsh_id);

    return program;
}
static GLuint CreateShader(GLenum shaderType, GLchar** src, GLsizei length)
{
    GLuint id = glCreateShader(shaderType);
    glShaderSource(id, length, src, NULL);
    glCompileShader(id);
    return id;
}
#endif