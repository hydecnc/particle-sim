#pragma once

#include <glm/glm.hpp>

class Particle {
public:
  const float m_radius{};
  glm::vec4 m_color{};
  glm::vec2 m_curPosition{};
  glm::vec2 m_prevPosition{};
  glm::vec2 m_acceleration{};

  Particle(float radius, const glm::vec4 &color, const glm::vec2 &position);

  void updatePosition(const float deltatime);
};
