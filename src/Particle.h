#pragma once

#include <glm/glm.hpp>

class Grid;

class Particle {
  friend class Grid;

public:
  const float m_radius{};
  const glm::vec4 m_color{};
  glm::vec2 m_curPosition{};
  glm::vec2 m_prevPosition{};

  Particle(float radius, const glm::vec4 &color, const glm::vec2 &position);

  void updatePosition(const float deltatime);
  void boost(const glm::vec2 &acceleration);

private:
  bool m_boost = false;
  glm::vec2 m_boostAcceleration{};
};
