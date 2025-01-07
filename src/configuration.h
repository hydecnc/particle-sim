#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace constants {
inline constexpr unsigned int scrWidth{800};
inline constexpr unsigned int scrHeight{800};
inline constexpr glm::vec3 backgroundColor{0.0f, 0.0f, 0.0f};
inline constexpr float aspectRatio{static_cast<float>(scrWidth) /
                                   static_cast<float>(scrHeight)};
inline constexpr float particleRadius{0.02f}; // radius of particle, from 0 to 1
inline constexpr int maxParticles{3000};
inline constexpr float containerRadius{
    0.9f}; // radius of container, from 0 to 1
inline constexpr glm::vec2 gravity{0.0f, -30.0f};
inline constexpr glm::vec2 acceleration{1.0f, -30.0f};
inline constexpr int numCells{static_cast<int>(2.0f / (particleRadius * 2))};
inline constexpr int maxParticlePerCell{4};
} // namespace constants
