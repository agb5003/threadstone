#include <GL/glew.h>

enum class BlendMode {
    Alpha,
    Additive,
    Multiply
};

class Renderer {
    GLuint shaderProgram;

    bool wireframe;
    BlendMode blendMode;
public:
    GLfloat anchorPointX;
    GLfloat anchorPointY;
    GLuint width;
    GLuint height;

    Renderer(GLfloat anchorPointX, GLfloat anchorPointY, GLuint width, GLuint height);
    void toggleWireframe();
};

class Pane {
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
public:
    Pane(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
    }
};

GLuint createDefaultShaderProgram();

// Renderer initializeRenderer(GLfloat anchorPointX, GLfloat anchorPointY, GLuint width, GLuint height, BlendMode blendMode);

GLuint createTriangleVAO();

GLuint createRectangleVAO(GLfloat anchorPointX, GLfloat anchorPointY, GLfloat width, GLfloat height);

GLuint createTriangleFanVAO();

void drawTriangleFan(GLuint VAO, GLuint shaderProgram);

void drawRectangle(GLuint VAO, GLuint shaderProgram);