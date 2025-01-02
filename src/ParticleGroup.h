#pragma once

#include "Container.h"
#include "Particle.h"
#include <vector>

class ParticleGroup {
public:
  ParticleGroup(Container::Container &container,
                const std::vector<Particle> particle);

  void setupBuffers();
  void render() const;
  void cleanUp();

  void updateParticles(float deltaTime);

  void addParticle(const Particle &particle);
  void removeParticle();

private:
  unsigned int m_VAO{};
  unsigned int m_VBO{};
  Container::Container &m_container;
  std::vector<Particle> m_particles{};
};
