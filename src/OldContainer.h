#pragma once

#include "Particle.h"
#include <glm/vec2.hpp>
#include <vector>

namespace Container {
class Container {
public:
  virtual ~Container() = default;

  virtual void setupBuffers() = 0;
  virtual void render() const = 0;
  virtual void cleanUp() = 0;
  virtual void applyConstraint(Particle &particle) const = 0;

protected:
  unsigned int m_VAO{};
  unsigned int m_VBO{};
};

class Circle : public Container {
public:
  Circle(float radius, glm::vec2 center);

  void setupBuffers() override;
  void setupBuffers(int numVertices);
  void render() const override;
  void cleanUp() override;
  void applyConstraint(Particle &particle) const override;

  float radius() const;
  float aspectRatio() const;
  const glm::vec2 &center() const;

private:
  std::vector<float> m_vertices{};
  float m_radius{};
  glm::vec2 m_center{};
};

}; // namespace Container
