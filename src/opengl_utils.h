#pragma once
// clang-format off
#include <glad/glad.h>
// clang-format on
#include "Container.h"
#include "Particle.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengles2.h>
#include <vector>

struct AppState {
  // SDL states
  SDL_Window *window{};
  // OpenGL states
  SDL_GLContext gl_context{};
  // Particle states
  std::vector<Particle> particles{};
  // Container
  CircleContainer container;
};

// inline void initializeOpenGL(AppState &state) {
//   glGenVertexArrays(1, &state.VAO);
//   glGenBuffers(1, &state.VBO);
//
//   glBindVertexArray(state.VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
//   glBufferData(GL_ARRAY_BUFFER, state.particles.size() * sizeof(Particle),
//                state.particles.data(), GL_STREAM_DRAW);
//
//   // Pass the radius of each particle as index 0
//   glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);
//   glEnableVertexAttribArray(0);
//
//   // Pass the color of each particle as index 1
//   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle),
//                         (void *)offsetof(Particle, m_color));
//   glEnableVertexAttribArray(1);
//
//   // Pass the position of each particle as index 2
//   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle),
//                         (void *)offsetof(Particle, m_curPosition));
//   glEnableVertexAttribArray(2);
//
//   glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
//   glBindVertexArray(state.VAO);
//
//   // Setup alpha blending to draw circles
//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// }
