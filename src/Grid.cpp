#include "Grid.h"
#include "configuration.h"
#include <iomanip>
#include <iostream>

Cell::Cell(const glm::vec2 &position) : m_position{position} {}

Grid::Grid() {
  for (int x{0}; x < m_width; ++x) {
    for (int y{0}; y < m_height; ++y) {
      const float normalizedX =
          static_cast<float>(x) / static_cast<float>(m_width) * 2.0f - 1.0f;
      const float normalizedY =
          static_cast<float>(y) / static_cast<float>(m_height) * 2.0f - 1.0f;
      m_cells[x][y] = Cell({normalizedX, normalizedY});
    }
  }
}

void Grid::clearGrid() {
  for (auto &row : m_cells) {
    for (auto &cell : row) {
      cell.particles = {};
    }
  }
}

void Grid::fillGrid(std::vector<Particle> &particles) {
  for (Particle &particle : particles) {
    const glm::vec2 gridPos{(particle.curPosition() + 1.0f) / 2.0f *
                            static_cast<float>(constants::gridSize - 1)};
    m_cells[static_cast<int>(gridPos.x)][static_cast<int>(gridPos.y)]
        .particles.push_back(particle);
  }
}

void Grid::updateGrid(std::vector<Particle> &particles) {
  clearGrid();
  fillGrid(particles);
}

// TODO: double check const and references
void Grid::solveCollisions() const {
  // printGrid();
  for (int x{1}; x < m_width - 1; ++x) {
    for (int y{1}; y < m_height - 1; ++y) {
      const Cell &currentCell{m_cells[x][y]};
      // iterate on all surrouding cells, including the current one
      for (int dx{-1}; dx <= 1; ++dx) {
        for (int dy{-1}; dy <= 1; ++dy) {
          const Cell &otherCell{m_cells[x + dx][y + dy]};
          checkCellCollisions(currentCell, otherCell);
        }
      }
    }
  }
}

void Grid::checkCellCollisions(const Cell &c1, const Cell &c2) const {
  for (Particle &p1 : c1.particles) {
    for (Particle &p2 : c2.particles) {
      if (&p1 != &p2) {
        p1.solveCollision(p2);
      }
    }
  }
}

void Grid::printGrid() const {
  for (const auto &row : m_cells) {
    for (const Cell &cell : row) {
      std::cout << std::setw(4) << cell.particles.size() << " ";
    }
    std::cout << '\n';
  }
}
