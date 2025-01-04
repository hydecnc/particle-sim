#pragma once
#include "Particle.h"
#include "configuration.h"
#include <array>
#include <functional>
#include <vector>

class Cell {
public:
  std::vector<std::reference_wrapper<Particle>> particles{};

  Cell() : m_position{0.0f, 0.0f} {} // Add this default constructor
  Cell(const glm::vec2 &position);

private:
  glm::vec2 m_position{}; // top-left corner
};

class Grid {
public:
  Grid();

  void clearGrid();
  void fillGrid(std::vector<Particle> &particles);
  void updateGrid(std::vector<Particle> &particles);
  void solveCollisions() const;
  void checkCellCollisions(const Cell &c1, const Cell &c2) const;

  void printGrid() const;

private:
  int m_width{constants::gridSize};
  int m_height{constants::gridSize};
  std::array<std::array<Cell, constants::gridSize>, constants::gridSize>
      m_cells{};
};
