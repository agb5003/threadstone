#define SDL_MAIN_USE_CALLBACKS 1
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/GLU.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>


#include <userinterface.h>
#include <renderer.h>


// SCRATCH REGION START




// SCRATCH REGION END



const std::string VERSION_NUMBER = "0.1";


struct AppState {
    // Window API
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;

    // Renderer
    Renderer renderer;
};

static AppState state;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    SDL_SetAppMetadata("Threadstone Engine", VERSION_NUMBER.c_str(), "com.agb5003.threadstone");

    // Initialize SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error initializing SDL3: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    // Set window title here
    std::string windowTitle = "Threadstone v" + VERSION_NUMBER;

    // Initialize the state variables
    state.window = SDL_CreateWindow(windowTitle.c_str(), 1000, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!state.window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }
    state.glContext = SDL_GL_CreateContext(state.window);
    if (!state.glContext) {
        std::cout << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
    }

    // Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error initializing GLEW: ", glewGetErrorString(err);
        return SDL_APP_FAILURE;
    }

    // SCRATCH: INITIALIZE RENDERER
    int winWidth; int winHeight;
    SDL_GetWindowSize(state.window, &winWidth, &winHeight);
    state.renderer = Renderer(0, 0, winWidth, winHeight);
    glViewport(0, 0, state.renderer.width, state.renderer.height);
    createRectangleVAO(-0.5, 0.5, 1, 1);

    // Collect state variables and store it for access in callback functions
    *appstate = &state;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto *state = static_cast<AppState*>(appstate);

    // Draw background
    glClearColor(0.3f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Test draw HUD
    drawUIElements(state->renderer.shaderProgram);

    SDL_GL_SwapWindow(state->window);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto *state = static_cast<AppState*>(appstate);
    
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                    return SDL_APP_SUCCESS;
            }
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            // Get new window size from event data
            state->renderer.width = event->window.data1;
            state->renderer.height = event->window.data2;
            // Call glViewport to adjust scaling upon window resize
            glViewport(0, 0, state->renderer.width, state->renderer.height);
            break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // auto *state = static_cast<AppState*>(appstate);

    SDL_Quit();
}