#include "Particle.h"
#include "Grid.h"
#include <iostream>

Particle::Particle(Grid *grid, float radius, const glm::vec4 &color,
                   const glm::vec2 &position)
    : m_grid{grid}, m_radius{radius}, m_color{color}, m_curPosition{position},
      m_prevPosition{position}, m_acceleration{0, -0.98}, m_prev{nullptr},
      m_next{nullptr} {
  grid->add(this);
}

void Particle::updatePosition(const float deltatime) {
  glm::vec2 newPosition{m_curPosition + m_curPosition - m_prevPosition +
                        m_acceleration * deltatime * deltatime};
  std::cout << newPosition.x << ' ' << newPosition.y << '\n';
  m_grid->move(this, newPosition);
  m_prevPosition = m_curPosition;
  m_curPosition = newPosition;
}
