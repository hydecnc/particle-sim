#include "Grid.h"
#include "configuration.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

void Cell::addParticle(Particle &particle) {
  if (m_particleCount < constants::maxParticlePerCell) {
    particles[m_particleCount] = &particle;
    ++m_particleCount;
  } else {
    std::cerr << "Fatal error: Too many particles in one cell (max: "
              << constants::maxParticlePerCell << ")\n";
    std::exit(EXIT_FAILURE); // Exit with error code 1
  }
}

void Cell::clear() { m_particleCount = 0; }

Grid::Grid() {
  for (int x{0}; x < constants::gridSize; ++x) {
    for (int y{0}; y < constants::gridSize; ++y) {
      m_cells[x][y] = Cell();
    }
  }
}

void Grid::clearGrid() {
  for (auto &row : m_cells) {
    for (auto &cell : row) {
      cell.clear();
    }
  }
}

void Grid::fillGrid(std::vector<Particle> &particles) {
  for (Particle &particle : particles) {
    const glm::vec2 gridPos{(particle.curPosition() + 1.0f) / 2.0f *
                            static_cast<float>(constants::gridSize - 1)};
    m_cells[std::floor(gridPos.x)][std::floor(gridPos.y)].addParticle(particle);
  }
}

void Grid::updateGrid(std::vector<Particle> &particles) {
  clearGrid();
  fillGrid(particles);
}

void Grid::solveCollisions() {
  for (int x{1}; x < constants::gridSize - 1; ++x) {
    for (int y{1}; y < constants::gridSize - 1; ++y) {
      Cell &currentCell{m_cells[x][y]};
      // iterate on all surrouding cells, including itself
      for (int dx{-1}; dx <= 1; ++dx) {
        for (int dy{-1}; dy <= 1; ++dy) {
          Cell &otherCell{m_cells[x + dx][y + dy]};
          checkCellCollisions(currentCell, otherCell);
        }
      }
    }
  }
}

void Grid::checkCellCollisions(Cell &c1, Cell &c2) const {
  for (Particle *p1 : c1.particles) {
    if (p1 == nullptr) {
      continue;
    }
    for (Particle *p2 : c2.particles) {
      if (p2 == nullptr || p1 == p2) {
        continue;
      }
      p1->solveCollision(*p2);
    }
  }
}
