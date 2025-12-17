#define SDL_MAIN_USE_CALLBACKS
#include "CircleContainer.h"
#include "configuration.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <vector>

unsigned int last_time{0};
unsigned int current_time{0};
unsigned int particle_add_counter{0};

struct AppState {
  SDL_Window *window{};
  SDL_GLContext gl_context{};
  CircleContainer container;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  // Initialize SDL3
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't intialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Setup window
  SDL_Window *window = SDL_CreateWindow("Constellation", conf::kWidth,
                                        conf::kHeight, SDL_WINDOW_OPENGL);
  if (!window) {
    SDL_Log("Couldn't create window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Set OpenGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  // Create OpenGL context
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (!gl_context) {
    SDL_Log("Couldn't create OpenGL context: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Load all OpenGL function pointers
  if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Failed to initialize GLAD");
    return SDL_APP_FAILURE;
  }
  SDL_GL_MakeCurrent(window, gl_context);

  std::vector<Particle> particles = {
      // Particle{
      //     conf::kParticleRadius,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {0.3, 0.6},
      // },
      // Particle{
      //     conf::kParticleRadius / 2,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {-0.4, 0.6},
      // },
      // Particle{
      //     conf::kParticleRadius,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {-0.2, 0.6},
      // },
      // Particle{
      //     conf::kParticleRadius,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {-0.3, 0.6},
      // },
      // Particle{
      //     conf::kParticleRadius,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {0.1, 0.6},
      // },
      // Particle{
      //     conf::kParticleRadius,
      //     {1.0, 0.0, 0.0, 1.0},
      //     {0.2, 0.6},
      // },
  };

  // Initialize OpenGL and creaete shaders
  const std::string shader_path{
      "/home/arete/devel/projects/cpp/particle_sim/src/shaders/"};
  Shader container_shader =
      Shader((shader_path + "circle_container.vert").c_str(),
             (shader_path + "circle_container.frag").c_str());
  Shader particle_shader = Shader((shader_path + "particle.vert").c_str(),
                                  (shader_path + "particle.frag").c_str());
  CircleContainer container =
      CircleContainer{particles, container_shader, particle_shader};
  container.setupContainerBuffers();
  container.setupParticleBuffers();

  *appstate = new AppState{window, gl_context, container};

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

  last_time = current_time;
  // Calculate deltatime  last_time = current_time;
  current_time = SDL_GetTicks();
  const float deltatime{static_cast<float>(current_time - last_time) / 1000};

  // print fps
  float fps{1.0f / deltatime};
  std::cout << "\rFPS: " << static_cast<int>(fps) << "    "
            << "Num particles: " << state.container.m_particles.size()
            << "     " << std::flush;

  // Clear previous frame
  glClearColor(conf::kBackgroundColor.r, conf::kBackgroundColor.g,
               conf::kBackgroundColor.b, conf::kBackgroundColor.a);
  glClear(GL_COLOR_BUFFER_BIT);

  particle_add_counter += 1;
  if (particle_add_counter >= conf::kParticleSpawnRate) {
    state.container.m_particles.push_back(Particle{
        conf::kParticleRadius,
        {1.0, 0.0, 0.0, 1.0},
        {0.2, 0.6},
    });
    particle_add_counter = 0;
  }
  state.container.drawContainer();
  state.container.updateParticles(deltatime);
  state.container.drawParticles();

  SDL_GL_SwapWindow(state.window);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState &state = *static_cast<AppState *>(appstate);
  // SDL3 cleans up the window/render for us.
  SDL_GL_DestroyContext(state.gl_context);
  state.container.cleanUp();
}
