#include "Particle.h"
#include "configuration.h"
#include <glm/geometric.hpp>
#include <iostream>

Particle::Particle(float radius, const glm::vec2 &curPosition,
                   const glm::vec2 &acceleration, const glm::vec3 &color)
    : m_radius{radius}, m_curPosition{curPosition}, m_prevPosition{curPosition},
      m_acceleration{acceleration}, m_color{color} {};

void Particle::accelerate(const glm::vec2 &acceleration) {
  m_acceleration += acceleration;
}

void Particle::updatePosition(float dt) {
  glm::vec2 newPosition =
      m_curPosition + m_curPosition - m_prevPosition + m_acceleration * dt * dt;
  m_prevPosition = m_curPosition;
  m_curPosition = newPosition;
  m_acceleration = {0, 0};
}

void Particle::solveCollision(Particle &particle) {
  glm::vec2 disp{m_curPosition - particle.curPosition()};
  disp.x *= constants::aspectRatio;

  const float dist{glm::length(disp)};

  if (dist < m_radius + particle.radius()) {
    const glm::vec2 n{disp / dist};
    const float delta{(m_radius + particle.radius()) - dist};
    glm::vec2 factor{0.5f * delta * n};
    factor.x /= constants::aspectRatio;

    m_curPosition += factor;
    particle.moidfyCurrentPosition(-1.0f * factor);
    std::cout << "Collision!" << '\n';
  }
}

// void Particle::solveCollision(std::vector<Particle> &particles, int index) {
//   for (int i{index}; i < particles.size(); ++i) {
//     Particle &particle{particles[i]};
//     glm::vec2 disp{m_curPosition - particle.curPosition()};
//     disp.x *= constants::aspectRatio;
//
//     const float dist{glm::length(disp)};
//
//     if (dist < m_radius + particle.radius()) {
//       const glm::vec2 n{disp / dist};
//       const float delta{(m_radius + particle.radius()) - dist};
//       glm::vec2 factor{0.5f * delta * n};
//       factor.x /= constants::aspectRatio;
//
//       m_curPosition += factor;
//       particle.moidfyCurrentPosition(-1.0f * factor);
//     }
//   }
// }

void Particle::print() const {
  std::cout << "Particle: (" << m_curPosition.x << ", " << m_curPosition.y
            << ")\n";
}

const glm::vec2 &Particle::curPosition() const { return m_curPosition; }
const glm::vec2 &Particle::prevPosition() const { return m_prevPosition; }
float Particle::radius() const { return m_radius; }
const glm::vec2 &Particle::acceleration() const { return m_acceleration; }

void Particle::setCurrentPosition(const glm::vec2 &position) {
  m_curPosition = position;
}

void Particle::moidfyCurrentPosition(const glm::vec2 &factor) {
  m_curPosition += factor;
}

void Particle::setPreviousPosition(const glm::vec2 &position) {
  m_prevPosition = position;
}
