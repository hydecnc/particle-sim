// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "ParticleGroup.h"
#include "Particle.h"
#include "configuration.h"
#include <iostream>

ParticleGroup::ParticleGroup(const Container::Container &container,
                             const std::vector<Particle> &particles)
    : m_container{container}, m_particles{particles} {
  m_particles.reserve(constants::maxParticles);
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(m_bufferCount, m_VBOs);
}

void ParticleGroup::setupBuffers() {
  // setup two VBOs
  for (int i{0}; i < m_bufferCount; ++i) {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[i]);
    glBufferData(GL_ARRAY_BUFFER, m_particles.capacity() * sizeof(Particle),
                 nullptr, GL_STREAM_DRAW);
  }

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
  // pass in position
  glVertexAttribPointer(
      0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle),
      nullptr); // nullptr because m_curPosition is the first attribute
  glEnableVertexAttribArray(0);

  // pass in color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle),
                        (void *)Particle::getColorOffset());
  glEnableVertexAttribArray(1);

  // pass in radius
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle),
                        (void *)Particle::getRadiusOffset());
  glEnableVertexAttribArray(2);
}

void ParticleGroup::render() {
  // swap buffers
  m_currentBuffer = (m_currentBuffer + 1) % m_bufferCount;

  glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[m_currentBuffer]);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_particles.size() * sizeof(Particle),
                  m_particles.data());

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_POINTS, 0, m_particles.size());
}

void ParticleGroup::cleanUp() const {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(m_bufferCount, m_VBOs);
}

void ParticleGroup::updateParticles(const float deltaTime) {
  constexpr int subSteps{8};
  const float subDeltaTime{deltaTime / static_cast<float>(subSteps)};

  // use substeps for better verlet simulation results
  for (int subStep{subSteps}; subStep > 0; --subStep) {
    for (Particle &particle : m_particles) {
      particle.accelerate(constants::gravity);
      m_container.applyConstraint(particle);
    }
    m_grid.updateGrid(m_particles);
    m_grid.solveCollisions();
    for (Particle &particle : m_particles) {
      particle.updatePosition(subDeltaTime);
    }
  }
}

void ParticleGroup::addParticle(const Particle &particle) {
  if (m_particles.size() >= m_particles.capacity()) {
    std::cerr << "Warning: Adding particle beyond buffer capacity\n";
  }
  m_particles.push_back(particle);
}

void ParticleGroup::removeParticle() {
  if (m_particles.empty()) {
    return;
  }
  m_particles.pop_back();
}

void ParticleGroup::printParticles() const {
  for (const Particle &particle : m_particles) {
    std::cout << '(' << particle.curPosition().x << ", "
              << particle.curPosition().y << "), ";
  }
}

int ParticleGroup::particleCount() const { return m_particles.size(); }
