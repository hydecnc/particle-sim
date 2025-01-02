// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "ParticleGroup.h"
#include "Particle.h"
#include "configuration.h"

ParticleGroup::ParticleGroup(Container::Container &container,
                             const std::vector<Particle> particles)
    : m_container{container}, m_particles{particles} {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
}

void ParticleGroup::setupBuffers() {
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle),
               m_particles.data(), GL_DYNAMIC_DRAW);

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

void ParticleGroup::render() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_particles.size() * sizeof(Particle),
               m_particles.data(), GL_DYNAMIC_DRAW);

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_POINTS, 0, m_particles.size());
}

void ParticleGroup::cleanUp() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void ParticleGroup::updateParticles(float deltaTime) {
  const int subSteps{8};
  const float subDeltaTime{deltaTime / static_cast<float>(subSteps)};

  // use substeps for better verlet simulation results
  for (int subStep{subSteps}; subStep > 0; --subStep) {
    int i{1}; // index to prevent redundant collision calculation
    for (Particle &particle : m_particles) {
      particle.accelerate(constants::gravity);
      m_container.applyConstraint(particle);
      particle.solveCollision(m_particles, i);
      particle.updatePosition(subDeltaTime);
      ++i;
    }
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
