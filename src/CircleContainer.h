#pragma once

#include "Grid.h"
#include "Particle.h"
#include "Shader.h"
#include "configuration.h"
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
  Grid m_grid{};

  struct Data {
    float m_radius{600};
    glm::vec2 m_position{0, 0};
    glm::vec4 m_color{conf::skyBlue};
  } m_data{};

  CircleContainer(std::vector<Particle> &particles,
                  const Shader &containerShader, const Shader &particleShader);

  void setupParticleBuffers();
  void setupContainerBuffers();

  void addParticle(Particle &particle);
  void updateParticles(const float deltatime);
  void drawContainer();
  void drawParticles();
  void applyConstraint(Particle &particle);
  void processCollisions();

  void cleanUp();
};
