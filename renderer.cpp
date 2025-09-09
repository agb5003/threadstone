// OpenGL render functions

#include <GL/glew.h>
#include <iostream>
#include <renderer.h>

// REPLACE LATER WITH CODE THAT TAKES IN VERTEX DATA
static float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
static float triangleFanVertices[] = {
      0.0f,  -0.5f, 0.0f,
     -0.5f,  0.25f, 0.0f,
    -0.25f,   0.5f, 0.0f,
     0.25f,   0.5f, 0.0f,
      0.5f,  0.25f, 0.0f
};

const char *defaultVertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *defaultFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 1.0f, 0.4f);\n"
    "}\0";

GLuint createDefaultShaderProgram() {

    // Create vertex shader
    // vertexShader is the ID of the shader, stored as unsigned int
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Store the ID returned by glCreateShader in vertexShader
    glShaderSource(vertexShader, 1, &defaultVertexShaderSource, NULL); // Specify source of shader
    glCompileShader(vertexShader);
    // Check if shader compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &defaultFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check if shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shader objects into a shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram(); // Store returned program ID in shaderProgram
    // Now attach the previously compiled shaders to the program and link them
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check if linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;

}

class Renderer {
private:
    GLuint shaderProgram;

    bool wireframe = false;
    BlendMode blendMode;
public:
    GLfloat anchorPointX;
    GLfloat anchorPointY;
    GLuint width = 1000;
    GLuint height = 1000;

    Renderer(GLfloat anchorPointX, GLfloat anchorPointY, GLuint width, GLuint height) {
        shaderProgram = createDefaultShaderProgram();
        anchorPointX = anchorPointX;
        anchorPointY = anchorPointY;
        width = width;
        height = height;

        // BLENDING OPTIONS
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void toggleWireframe() {
        wireframe = true;       
    }

    void draw() {
        // Make sure wireframe mode is correct
        switch (wireframe) {
            case true:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case false:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
        }
        // Make sure blend mode is correct
        switch (blendMode) {
            case BlendMode::Alpha:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case BlendMode::Additive:
                glBlendFunc(GL_ONE, GL_ONE);
                break;
            case BlendMode::Multiply:
                glBlendFunc(GL_DST_COLOR, GL_ZERO);
                break;
        }

    }
};

// Renderer initializeRenderer(GLfloat anchorPointX, GLfloat anchorPointY, GLuint width, GLuint height, BlendMode blendMode) {
//     // TODO: Create default shader program
//     Renderer renderer;
//     
//     return renderer;
// }

GLuint createTriangleVAO() {
    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO); // Create a VAO
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO); // Generate 1 buffer at the address of VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO to modify it
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); // Copy data to VBO
    // read more: https://docs.gl/gl4/glBufferData
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // note: file://./notes/vertex-attrib.png
    glEnableVertexAttribArray(0);
    
    return VAO;
}

GLuint createRectangleVAO(GLfloat anchorPointX, GLfloat anchorPointY, GLfloat width, GLfloat height) {
    // NOTE: Parameters are in NDC
    
    GLuint VAO;
    GLuint VBO; // buffer containing vertex drawing order
    glGenBuffers(1, &VBO);
    GLuint EBO; // buffer containing vertex positions
    glGenBuffers(1, &EBO);

    // Position of the vertices
    GLfloat vertices[] = {
        anchorPointX + width, anchorPointY + height, 0.0f, // top right
        anchorPointX + width,          anchorPointY, 0.0f, // bottom right
        anchorPointX,          anchorPointY, 0.0f, // bottom left
        anchorPointX, anchorPointY + height, 0.0f, // top left
    };

    // Decides the order the vertices are drawn
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

GLuint createTriangleFanVAO() {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleFanVertices), triangleFanVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

void drawTriangleFan(GLuint VAO, GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
    // see how the mode parameter in glDrawArrays influence how vertices are connected:
    // file://./notes/modes.gif
}


void drawRectangle(GLuint VAO, GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}