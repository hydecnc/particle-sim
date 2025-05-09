#include "Container.h"
// clang-format off
#include <glad/glad.h>
// clang-format on
#include "Shader.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>

CircleContainer::CircleContainer(const std::vector<Particle> &particles,
                                 const Shader &containerShader,
                                 const Shader &particleShader)
    : m_particles{particles}, m_containerShader{containerShader},
      m_particleShader{particleShader} {
  setupContainerBuffers();
  setupParticleBuffers();
}

void CircleContainer::setupContainerBuffers() {
  glGenVertexArrays(1, &m_containerVAO);
  glGenBuffers(1, &m_containerVBO);

  glBindVertexArray(m_containerVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_containerVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Data), &m_data, GL_STATIC_DRAW);

  // Pass the radius of the container at index 0
  glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Data), nullptr);
  glEnableVertexAttribArray(0);

  // Pass the position of the container at index 1
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Data),
                        (void *)offsetof(Data, m_position));
  glEnableVertexAttribArray(1);

  // Pass the color of the container at index 2
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Data),
                        (void *)offsetof(Data, m_color));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, m_containerVBO);
  glBindVertexArray(m_containerVAO);

  // Setup alpha blending to draw circles
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CircleContainer::setupParticleBuffers() {
  glGenVertexArrays(1, &m_particlesVAO);
  glGenBuffers(1, &m_particlesVBO);

  glBindVertexArray(m_particlesVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_particlesVBO);
  glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle),
               m_particles.data(), GL_STREAM_DRAW);

  // Pass the radius of each particle as index 0
  glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);
  glEnableVertexAttribArray(0);

  // Pass the color of each particle as index 1
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle),
                        (void *)offsetof(Particle, m_color));
  glEnableVertexAttribArray(1);

  // Pass the position of each particle as index 2
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle),
                        (void *)offsetof(Particle, m_curPosition));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, m_particlesVBO);
  glBindVertexArray(m_particlesVAO);

  // Setup alpha blending to draw circles
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CircleContainer::drawContainer() {
  m_containerShader.use();

  glBindBuffer(GL_ARRAY_BUFFER, m_containerVBO);
  glBindVertexArray(m_containerVAO);
  glDrawArrays(GL_POINTS, 0, 1);
}

void CircleContainer::drawParticles(float deltatime) {
  m_particleShader.use();

  glBindBuffer(GL_ARRAY_BUFFER, m_particlesVBO);
  for (auto &particle : m_particles) {
    particle.updatePosition(deltatime);
    // std::cout << "Updated position: " << particle.m_curPosition.x << ", "
    //           << particle.m_curPosition.y << '\n';
  }
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_particles.size() * sizeof(Particle),
                  m_particles.data());

  glBindVertexArray(m_particlesVAO);
  glDrawArrays(GL_POINTS, 0, m_particles.size());
}

void CircleContainer::cleanUp() {
  glDeleteVertexArrays(1, &m_containerVAO);
  glDeleteVertexArrays(1, &m_particlesVAO);
  glDeleteBuffers(1, &m_containerVBO);
  glDeleteBuffers(1, &m_particlesVBO);
  glDeleteProgram(m_containerShader.programId);
  glDeleteProgram(m_particleShader.programId);
}
