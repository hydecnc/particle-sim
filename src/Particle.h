#pragma once

#include <glm/glm.hpp>

class Grid;

class Particle {
  friend class Grid;

public:
  const float m_radius{};
  glm::vec4 m_color{};
  glm::vec2 m_curPosition{};
  glm::vec2 m_prevPosition{};
  glm::vec2 m_acceleration{};

  Particle(Grid *grid, float radius, const glm::vec4 &color,
           const glm::vec2 &position);

  void updatePosition(const float deltatime);

private:
  Grid *m_grid;
  Particle *m_prev;
  Particle *m_next;
};
