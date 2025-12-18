#include "Grid.h"
#include "Particle.h"
#include "configuration.h"
#include "glm/fwd.hpp"
#include <iostream>

Grid::Grid() { clearGrid(); }

void Grid::clearGrid() {
  for (int x{0}; x < conf::kNumCells; x++) {
    for (int y{0}; y < conf::kNumCells; y++) {
      m_cells[x][y] = {};
    }
  }
}

void Grid::add(Particle *particle) {
  glm::vec2 normalizedPosition = (particle->m_curPosition + 1.0f) / 2.0f;
  int cellX{static_cast<int>(normalizedPosition.x * conf::kNumCells)};
  int cellY{static_cast<int>(normalizedPosition.y * conf::kNumCells)};

  m_cells[cellX][cellY].push_back(particle);
}

void Grid::handleCollision() {
  for (int x{0}; x < conf::kNumCells; x++) {
    for (int y{0}; y < conf::kNumCells; y++) {
      handleCell(x, y);
    }
  }
}

void Grid::handleCell(const int x, const int y) {
  std::vector<Particle *> particles{m_cells[x][y]};
  for (int i{0}; i < particles.size(); i++) {
    Particle *particle = particles[i];
    for (int j{i + 1}; j < particles.size(); j++) {
      handleParticle(particle, particles[j]);
    }

    if (x > 0 && y > 0)
      handleParticles(particle, m_cells[x - 1][y - 1]);
    if (x > 0)
      handleParticles(particle, m_cells[x - 1][y]);
    if (y > 0)
      handleParticles(particle, m_cells[x][y - 1]);
    if (x > 0 && y < conf::kNumCells - 1)
      handleParticles(particle, m_cells[x - 1][y + 1]);
  }
}

void Grid::handleParticles(Particle *particle,
                           const std::vector<Particle *> &others) {
  for (auto other : others) {
    handleParticle(particle, other);
  }
}

void Grid::handleParticle(Particle *particle, Particle *other) {
  // handle collision between two particles
  const float particle_radius{particle->m_radius / conf::kHeight};
  const float other_radius{other->m_radius / conf::kHeight};
  glm::vec2 collision_axis{particle->m_curPosition - other->m_curPosition};
  collision_axis.x *= conf::aspectRatio;
  const float dist{glm::length(collision_axis)};
  if (dist < particle_radius + other_radius) {
    glm::vec2 n{collision_axis / dist};
    const float delta{(particle_radius + other_radius) - dist};
    particle->m_curPosition += 0.5f * delta * n;
    other->m_curPosition -= 0.5f * delta * n;
  }
}

void Grid::updateGrid(std::vector<Particle> &particles) {
  clearGrid();
  for (auto &particle : particles) {
    add(&particle);
  }
}
