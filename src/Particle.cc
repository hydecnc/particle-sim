#include "Particle.h"

Particle::Particle(float radius, const glm::vec4 &color,
                   const glm::vec2 &position)
    : m_radius{radius}, m_color{color} {
  m_curPosition = position;
  m_prevPosition = position;
  m_acceleration = {0, -0.98};
}

void Particle::updatePosition(const float deltatime) {
  glm::vec2 newPosition{m_curPosition + m_curPosition - m_prevPosition +
                        m_acceleration * deltatime * deltatime};
  m_prevPosition = m_curPosition;
  m_curPosition = newPosition;
}
