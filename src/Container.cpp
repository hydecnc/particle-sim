#include "Container.h"
#include "configuration.h"
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <cmath>
#include <glm/geometric.hpp>

Container::Circle::Circle(float radius, glm::vec2 center)
    : m_radius{radius}, m_center{center} {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
}

void Container::Circle::setupBuffers() { setupBuffers(100); }

void Container::Circle::setupBuffers(int numVertices) {
  // calculate vertices
  for (int i{0}; i < numVertices; ++i) {
    const float angle =
        2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numVertices);
    m_vertices.push_back((m_center.x + m_radius * cos(angle)) /
                         constants::aspectRatio);
    m_vertices.push_back(m_center.y + m_radius * sin(angle));
  }

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
               m_vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
}

void Container::Circle::render() const {
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_LINE_LOOP, 0, m_vertices.size() / 2);
}

void Container::Circle::cleanUp() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void Container::Circle::applyConstraint(Particle &particle) {
  glm::vec2 disp{particle.curPosition() - m_center};
  disp.x *= constants::aspectRatio;
  const float dist{glm::length(disp)};

  if (dist > (m_radius - particle.radius())) {
    const glm::vec2 n{glm::normalize(disp)};
    glm::vec2 newPos{m_center + n * (m_radius - particle.radius())};
    newPos.x /= constants::aspectRatio;
    particle.setCurrentPosition(newPos);
  }
}

float Container::Circle::radius() const { return m_radius; };
const glm::vec2 &Container::Circle::center() const { return m_center; }
