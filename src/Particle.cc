#include "Particle.h"
#include "configuration.h"

Particle::Particle(float radius, const glm::vec4 &color,
                   const glm::vec2 &position)
    : m_radius{radius}, m_color{color}, m_curPosition{position},
      m_prevPosition{position}, m_boostAcceleration{0, 0} {}

void Particle::updatePosition(const float deltatime) {
  glm::vec2 totalAccel{conf::kGravity};
  if (m_boost) {
    totalAccel += m_boostAcceleration;
    m_boost = false;
  }
  glm::vec2 newPosition{m_curPosition +
                        (m_curPosition - m_prevPosition) * 0.99f +
                        totalAccel * deltatime * deltatime};
  m_prevPosition = m_curPosition;
  m_curPosition = newPosition;
}

void Particle::boost(const glm::vec2 &acceleration) {
  m_boost = true;
  m_boostAcceleration = acceleration;
}
