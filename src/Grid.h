#pragma once
#include "Particle.h"
#include "configuration.h"

class Grid {
public:
  Grid();
  void add(Particle *particle);
  void handleCollision();
  void handleParticle(Particle *particle, Particle *other);
  void handleParticles(Particle *particle,
                       const std::vector<Particle *> &others);
  void handleCell(const int x, const int y);
  void updateGrid(std::vector<Particle> &particles);

private:
  void clearGrid();

private:
  std::vector<Particle *> m_cells[conf::kNumCells][conf::kNumCells];
};
