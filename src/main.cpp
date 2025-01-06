// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <glm/fwd.hpp>

#include <iostream>
#include <vector>

#include "shader_s.h"
#include "random.h"
#include "Particle.h"
#include "Container.h"
#include "ParticleGroup.h"
#include "configuration.h"
// clang-format on

// function declaration
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, ParticleGroup &particleGroup);

// boolean to prevent repeated kepresses for every frame
bool spacePressed{false};
int framecount{0};

// initial particles
const std::vector<Particle> initialParicles{};

// timing
float deltaTime{0.0f};
// float deltaTime{0.01667f};
float lastFrame{0.0f};

int main() {
  // glfw initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window setup
  GLFWwindow *window{glfwCreateWindow(constants::scrWidth, constants::scrHeight,
                                      "Particle Simulation GL", nullptr,
                                      nullptr)};
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(
      window,
      framebuffer_size_callback); // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // build and compile shaders
  const std::string shader_path{static_cast<std::string>(PROJECT_DIR) +
                                "/src/shaders/"};
  Shader particleShader{
      (shader_path + "particle.vert").c_str(),
      (shader_path + "particle.frag").c_str(),
  };
  Shader containerShader{
      (shader_path + "container.vert").c_str(),
      (shader_path + "container.frag").c_str(),
  };

  // setup container & particle group
  Container::Circle container{constants::containerRadius, {0.0f, 0.0f}};
  ParticleGroup particleGroup{container, initialParicles};
  particleGroup.setupBuffers();
  container.setupBuffers();

  // activate shaders & set uniforms
  particleShader.use();
  particleShader.setFloat("toPixel", constants::scrHeight * 2.0f);

  // display window & wait until it is visible on the screen
  glfwShowWindow(window);
  while (!glfwGetWindowAttrib(window, GLFW_VISIBLE)) {
    glfwWaitEvents();
  }

  // main loop
  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    float currentFrame{static_cast<float>(glfwGetTime())};
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // process input
    processInput(window, particleGroup);

    // add particles
    if (framecount >= 10) {
      particleGroup.addParticle({Random::get(constants::particleRadius / 2,
                                             constants::particleRadius),
                                 {0.0, 0.8},
                                 constants::acceleration,
                                 {0.6f, 0.6f, 0.3f}});
      framecount = 0;
    }
    ++framecount;

    // FPS counter
    std::cout << "FPS: " << 1.0f / deltaTime << '\n';

    // render
    glClearColor(constants::backgroundColor.r, constants::backgroundColor.g,
                 constants::backgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw container
    containerShader.use();
    container.render();

    // activate particleShader & update particles
    particleShader.use();
    particleGroup.updateParticles(deltaTime);
    particleGroup.render();

    // swap bufferes & poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  std::cout << "Particle Count: " << particleGroup.particleCount() << '\n';

  // cleaup
  container.cleanUp();
  particleGroup.cleanUp();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, ParticleGroup &particleGroup) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    spacePressed = false;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if (!spacePressed) {
      spacePressed = true;
      particleGroup.addParticle({Random::get(constants::particleRadius / 2,
                                             constants::particleRadius),
                                 {0.4, 0.6},
                                 constants::gravity,
                                 {
                                     Random::get(0.0f, 1.0f),
                                     Random::get(0.0f, 1.0f),
                                     Random::get(0.0f, 1.0f),
                                 }});
    }
  }
  if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
    particleGroup.removeParticle();
  }
}
