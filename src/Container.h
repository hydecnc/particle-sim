#pragma once

#include "Particle.h"
#include "Shader.h"
#include <vector>

class CircleContainer {
public:
  GLuint m_containerVAO{};
  GLuint m_containerVBO{};
  GLuint m_particlesVAO{};
  GLuint m_particlesVBO{};

  Shader m_containerShader{};
  Shader m_particleShader{};

  std::vector<Particle> m_particles{};

  struct Data {
    float m_radius{600};
    glm::vec2 m_position{0, 0};
    glm::vec4 m_color{79.0f / 255.0f, 195.0f / 255.0f, 247.0f / 255.0f, 1.0f};
  } m_data{};

  CircleContainer(const std::vector<Particle> &particles,
                  const Shader &containerShader, const Shader &particleShader);

  void setupParticleBuffers();
  void setupContainerBuffers();

  void updateParticles(const float deltatime);
  void drawContainer();
  void drawParticles();
  void applyConstraint(Particle &particle);
  void checkCollisions();

  void cleanUp();
};
