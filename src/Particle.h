#pragma once

#include <glm/vec2.hpp>

class Particle {
public:
  Particle(float radius, glm::vec2 curPosition, glm::vec2 acceleration);

  void updatePosition(float dt);
  void accelerate(glm::vec2 acc);
  void print() const;

  glm::vec2 curPosition() const;
  glm::vec2 prevPosition() const;
  float radius() const;
  void setCurrentPosition(glm::vec2 position);
  void setPreviousPosition(glm::vec2 position);

private:
  glm::vec2 m_curPosition{};
  glm::vec2 m_prevPosition{};
  glm::vec2 m_acceleration{};
  float m_radius{};
};
