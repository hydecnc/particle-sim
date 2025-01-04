#pragma once

#include "Container.h"
#include "Grid.h"
#include "Particle.h"
#include <vector>

class ParticleGroup {
public:
  ParticleGroup(const Container::Container &container,
                const std::vector<Particle> &particles);

  void setupBuffers();
  void render();
  void cleanUp() const;

  void updateParticles(float deltaTime);

  void addParticle(const Particle &particle);
  void removeParticle();

  void printParticles() const;
  int particleCount() const;

private:
  static const int m_bufferCount{2};

  unsigned int m_VAO{};
  unsigned int m_VBOs[m_bufferCount]{};
  int m_currentBuffer{0};
  const Container::Container &m_container;
  Grid m_grid{};
  std::vector<Particle> m_particles{};
};
