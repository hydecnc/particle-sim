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
// clang-format on

// function declaration
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, ParticleGroup &particleGroup);

// settings / contants
const unsigned int SCR_WIDTH{800};
const unsigned int SCR_HEIGHT{800};
const float PARTICLE_RADIUS{0.03f}; // radius of particle, from 0 to 1
const float CONTAINER_RADIUS{0.9f}; // radius of container, from 0 to 1
const glm::vec2 GRAVITY{0.0f, -30.0f};

// particles
std::vector<Particle> particles{
    // {{0.5f, 0.0f}, GRAVITY},
    {PARTICLE_RADIUS, {-0.5f, 0.0f}, GRAVITY},
    // {{0.0f, 0.5f}, GRAVITY},
};

// timing
float deltaTime{0.0f};
float lastFrame{0.0f};

int main() {
  // glfw initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window setup
  GLFWwindow *window{glfwCreateWindow(
      SCR_WIDTH, SCR_HEIGHT, "Particle Simulation GL", nullptr, nullptr)};
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
  Container::Circle container{CONTAINER_RADIUS,
                              {0.0f, 0.0f},
                              static_cast<float>(SCR_WIDTH) /
                                  static_cast<float>(SCR_HEIGHT)};
  ParticleGroup particleGroup{container, particles};
  particleGroup.setupBuffers();
  container.setupBuffers();

  // activate shaders & set uniforms
  particleShader.use();
  particleShader.setFloat("radius", PARTICLE_RADIUS * SCR_HEIGHT * 2.0f);

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

    // render
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    containerShader.use();
    // draw container
    container.render();

    // activate particleShader & update particles
    particleShader.use();
    particleGroup.updateParticles(deltaTime);
    particleGroup.render();

    // swap bufferes & poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    particleGroup.addParticle(
        {PARTICLE_RADIUS,
         {Random::get(-1.0f, 1.0f), Random::get(-1.0f, 1.0f)},
         GRAVITY});
  }
  if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
    particleGroup.removeParticle();
  }
}
