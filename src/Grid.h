#pragma once
#include "Particle.h"
#include "configuration.h"

class Grid {
public:
  Grid();
  void add(Particle *particle);
  void handleCollision();
  void handleParticle(Particle *particle, Particle *other);
  void handleCell(const int x, const int y);
  void move(Particle *particle, const glm::vec2 &position);

private:
  void clearGrid();

private:
  Particle *m_cells[conf::kNumCells][conf::kNumCells];
};
