// This file contains functions defining how to draw each UI element, and a function that manages
// the draw calls according to the respective parameters and layout of the screen.

#include <iostream>
#include <renderer.h>
#include <GL/glew.h>

class UIElement {
private:
    GLuint shaderProgram;
public:
    bool visible = true;

    UIElement() {
        shaderProgram = createDefaultShaderProgram();
    }
};

// TODO
void drawUIElements() {
    // TODO: Issue draw calls to all visible elements, something to below's effect
    // for (element : elements) {
    //     if (!element.visible) continue;
    //     element.draw();
    // }

    // TODO: Replace below with above code when finished
    GLuint rectangleVAO = createRectangleVAO(-0.5, -0.5, 1, 1);
    // drawRectangle(rectangleVAO, shaderProgram);
    GLuint triangleFanVAO = createTriangleFanVAO();
    // drawTriangleFan(triangleFanVAO, shaderProgram);
}

// TODO
void drawWindow() {

}

// TODO
void drawNotification() {
    // TODO: Render text content (limit: 500 characters)
    
    // TODO: Draw rounded rectangle with size according to size of content

}