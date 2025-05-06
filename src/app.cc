#define SDL_MAIN_USE_CALLBACKS
#include "Shader.h"
#include "configuration.h"
#include "opengl_utils.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <vector>

unsigned int last_time{0};
unsigned int current_time{0};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  // Create AppState and assign it to appstate
  *appstate = new AppState{};
  AppState &state = *static_cast<AppState *>(*appstate);

  // Initialize SDL3
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't intialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Setup window
  state.window = SDL_CreateWindow("Constellation", 800, 800, SDL_WINDOW_OPENGL);
  if (!state.window) {
    SDL_Log("Couldn't create window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Set OpenGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  // Create OpenGL context
  state.gl_context = SDL_GL_CreateContext(state.window);
  if (!state.gl_context) {
    SDL_Log("Couldn't create OpenGL context: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Load all OpenGL function pointers
  if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Failed to initialize GLAD");
    return SDL_APP_FAILURE;
  }
  SDL_GL_MakeCurrent(state.window, state.gl_context);

  state.particles = {
      Particle{10.0, {1.0, 0.0, 0.0, 1.0}},
      // Particle{20.0, {0.0, 1.0, 0.0, 1.0}},
  };

  // Initialize OpenGL and creaete shaders
  initializeOpenGL(state);

  const std::string shader_path{
      "/home/voidy/devel/projects/cpp/particle_sim/src/shaders/"};
  state.shader = Shader((shader_path + "particle.vert").c_str(),
                        (shader_path + "particle.frag").c_str());

  SDL_Log("Application started successfully!");

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT)
    return SDL_APP_SUCCESS;
  else if (event->type == SDL_EVENT_KEY_DOWN) {
    if (event->key.key == SDLK_Q)
      return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState &state = *static_cast<AppState *>(appstate);

  // Calculate deltatime
  last_time = current_time;
  current_time = SDL_GetTicks();
  float deltatime{static_cast<float>(current_time - last_time) / 1000};

  // Clear previous frame
  glClearColor(conf::backgroundColor.r, conf::backgroundColor.g,
               conf::backgroundColor.b, conf::backgroundColor.a);
  glClear(GL_COLOR_BUFFER_BIT);

  // Activate shader
  state.shader.use();
  // state.shader.setFloat("radius", kStarSize);

  glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
  for (auto &particle : state.particles) {
    particle.updatePosition(deltatime);
    std::cout << "Updated position: " << particle.m_curPosition.x << ", "
              << particle.m_curPosition.y << '\n';
  }
  glBufferSubData(GL_ARRAY_BUFFER, 0, state.particles.size() * sizeof(Particle),
                  state.particles.data());

  glBindVertexArray(state.VAO);
  glDrawArrays(GL_POINTS, 0, state.particles.size());

  SDL_GL_SwapWindow(state.window);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState &state = *static_cast<AppState *>(appstate);
  // SDL3 cleans up the window/render for us.
  SDL_GL_DestroyContext(state.gl_context);
  glDeleteVertexArrays(1, &state.VAO);
  glDeleteBuffers(1, &state.VBO);
  glDeleteProgram(state.shader.programId);
}
