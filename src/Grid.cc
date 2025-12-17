#include "Grid.h"
#include "Particle.h"
#include "configuration.h"
#include "glm/fwd.hpp"
#include <iostream>

Grid::Grid() { clearGrid(); }

void Grid::clearGrid() {
  for (int x{0}; x < conf::kNumCells; x++) {
    for (int y{0}; y < conf::kNumCells; y++) {
      m_cells[x][y] = nullptr;
    }
  }
}

void Grid::add(Particle *particle) {
  int cellX{static_cast<int>(particle->m_curPosition.x * conf::kNumCells)};
  int cellY{static_cast<int>(particle->m_curPosition.y * conf::kNumCells)};
  std::cout << "Adding particle at " << particle->m_curPosition.x << ", "
            << particle->m_curPosition.y << " with grid " << cellX << ' '
            << cellY << '\n';

  particle->m_prev = nullptr;
  particle->m_next = m_cells[cellX][cellY];
  m_cells[cellX][cellY] = particle;

  if (particle->m_next != nullptr) {
    particle->m_next->m_prev = particle;
  }
}

void Grid::handleCollision() {
  for (int x{0}; x < conf::kNumCells; x++) {
    for (int y{0}; y < conf::kNumCells; y++) {
      handleCell(x, y);
    }
  }
}

void Grid::handleCell(const int x, const int y) {
  Particle *particle{m_cells[x][y]};
  while (particle != nullptr) {
    handleParticle(particle, particle->m_next);

    if (x > 0 && y > 0)
      handleParticle(particle, m_cells[x - 1][y - 1]);
    if (x > 0)
      handleParticle(particle, m_cells[x - 1][y]);
    if (y > 0)
      handleParticle(particle, m_cells[x][y - 1]);
    if (x > 0 && y < conf::kNumCells - 1)
      handleParticle(particle, m_cells[x - 1][y + 1]);

    particle = particle->m_next;
  }
}

void Grid::handleParticle(Particle *particle, Particle *other) {
  while (other != nullptr) {
    // handle collision between two particles
    const float particle_radius{particle->m_radius / conf::kHeight};
    const float other_radius{other->m_radius / conf::kHeight};
    glm::vec2 collision_axis{particle->m_curPosition - other->m_curPosition};
    collision_axis.x *= conf::aspectRatio;
    const float dist{glm::length(collision_axis)};
    if (dist < particle_radius + other_radius) {
      glm::vec2 n{collision_axis / dist};
      const float delta{(particle_radius + other_radius) - dist};
      move(particle, particle->m_curPosition + 0.5f * delta * n);
      move(other, other->m_curPosition - 0.5f * delta * n);
    }

    other = other->m_next;
  }
}

void Grid::move(Particle *particle, const glm::vec2 &position) {
  int oldCellX{static_cast<int>(particle->m_curPosition.x * conf::kNumCells)};
  int oldCellY{static_cast<int>(particle->m_curPosition.y * conf::kNumCells)};
  int cellX{static_cast<int>(position.x * conf::kNumCells)};
  int cellY{static_cast<int>(position.y * conf::kNumCells)};

  particle->m_prevPosition = particle->m_curPosition;
  particle->m_curPosition = position;

  if (oldCellX == cellX && oldCellY == cellY)
    return;

  // Unlink particle from the list of its old cell
  if (particle->m_prev != nullptr) {
    particle->m_prev->m_next = particle->m_next;
  }
  if (particle->m_next != nullptr) {
    particle->m_next->m_prev = particle->m_prev;
  }

  // If particle is the head of list, remove it
  if (m_cells[oldCellX][oldCellY] == particle) {
    m_cells[oldCellX][oldCellY] = particle->m_next;
  }

  add(particle);
}
