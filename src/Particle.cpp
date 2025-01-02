#include "Particle.h"
#include <glm/vec2.hpp>
#include <iostream>

Particle::Particle(float radius, glm::vec2 curPosition, glm::vec2 acceleration)
    : m_radius{radius}, m_curPosition{curPosition},
      m_acceleration{acceleration} {};

void Particle::updatePosition(float dt) {
  m_prevPosition = m_curPosition;
  m_curPosition =
      m_curPosition + m_curPosition - m_prevPosition + m_acceleration * dt * dt;
  m_acceleration = {0, 0};
}

void Particle::accelerate(glm::vec2 acceleration) {
  m_acceleration += acceleration;
}

void Particle::print() const {
  std::cout << "Particle: (" << m_curPosition.x << ", " << m_curPosition.y
            << ")\n";
}

glm::vec2 Particle::curPosition() const { return m_curPosition; }
glm::vec2 Particle::prevPosition() const { return m_prevPosition; }
float Particle::radius() const { return m_radius; }

void Particle::setCurrentPosition(glm::vec2 position) {
  m_curPosition = position;
}

void Particle::setPreviousPosition(glm::vec2 position) {
  m_prevPosition = position;
}
