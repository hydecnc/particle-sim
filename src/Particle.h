#pragma once

#include <cstddef>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Particle {
public:
  Particle(float radius, const glm::vec2 &curPosition,
           const glm::vec2 &acceleration, const glm::vec3 &color);

  void updatePosition(float dt);
  void accelerate(const glm::vec2 &acc);
  void solveCollision(Particle &particle);
  void print() const;

  const glm::vec2 &curPosition() const;
  const glm::vec2 &prevPosition() const;
  float radius() const;
  const glm::vec2 &acceleration() const;
  void setCurrentPosition(const glm::vec2 &position);
  void moidfyCurrentPosition(const glm::vec2 &factor);
  void setPreviousPosition(const glm::vec2 &position);

  static constexpr std::size_t getColorOffset() {
    return offsetof(Particle, m_color);
  }
  static constexpr std::size_t getRadiusOffset() {
    return offsetof(Particle, m_radius);
  }

private:
  glm::vec2 m_curPosition{};
  glm::vec2 m_prevPosition{};
  glm::vec2 m_acceleration{};
  float m_radius{};

  glm::vec3 m_color{};
};
