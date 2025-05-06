#include "Particle.h"

Particle::Particle(float radius, const glm::vec4 &color)
    : m_radius{radius}, m_color{color} {
  m_curPosition = {0, 0};
  m_prevPosition = {0, 0};
  m_acceleration = {0, -0.98};
}

void Particle::updatePosition(const float deltatime) {
  glm::vec2 newPosition{m_curPosition + m_curPosition - m_prevPosition +
                        m_acceleration * deltatime * deltatime};
  m_prevPosition = m_curPosition;
  m_curPosition = newPosition;
}
