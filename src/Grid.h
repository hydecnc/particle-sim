#pragma once
#include "Particle.h"
#include "configuration.h"
#include <array>
#include <vector>

class Cell {
public:
  static constexpr int maxParticles{constants::maxParticlePerCell};
  std::array<Particle *, maxParticles> particles{};

  void addParticle(Particle &particle);
  void clear();

private:
  int m_particleCount{0};
};

class Grid {
public:
  Grid();

  void clearGrid();
  void fillGrid(std::vector<Particle> &particles);
  void updateGrid(std::vector<Particle> &particles);
  void solveCollisions();
  void checkCellCollisions(Cell &c1, Cell &c2) const;

private:
  std::array<std::array<Cell, constants::gridSize>, constants::gridSize>
      m_cells{};
};
