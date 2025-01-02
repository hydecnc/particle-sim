// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "ParticleGroup.h"

ParticleGroup::ParticleGroup(Container::Container &container,
                             const std::vector<Particle> particles)
    : m_container{container}, m_particles{particles} {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
}

void ParticleGroup::setupBuffers() {
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(m_particles),
               m_particles.data(), GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(m_particles), nullptr);
  glEnableVertexAttribArray(0);
}

void ParticleGroup::render() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(m_particles),
               m_particles.data(), GL_DYNAMIC_DRAW);

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_POINTS, 0, m_particles.size());
}

void ParticleGroup::cleanUp() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void ParticleGroup::updateParticles(float deltaTime) {
  for (Particle &particle : m_particles) {
    particle.accelerate({0.0, -30.0});
    particle.updatePosition(deltaTime);
    m_container.applyConstraint(particle);
  }
}

void ParticleGroup::addParticle(const Particle &particle) {
  m_particles.push_back(particle);
}

void ParticleGroup::removeParticle() {
  if (m_particles.empty()) {
    return;
  }
  m_particles.pop_back();
}
