#pragma once

#include <glm/glm.hpp>

namespace conf {
inline constexpr unsigned int kWidth{800};
inline constexpr unsigned int kHeight{600};
inline constexpr glm::vec4 kBackgroundColor{0.1f, 0.1f, 0.1f, 1.0f};
inline constexpr float aspectRatio{static_cast<float>(kWidth) /
                                   static_cast<float>(kHeight)};
inline constexpr float kParticleRadius{20.0f};
inline constexpr int maxParticles{3000};
inline constexpr float containerRadius{
    0.9f}; // radius of container, from 0 to 1
inline constexpr glm::vec2 gravity{0.0f, -30.0f};
inline constexpr glm::vec2 acceleration{1.0f, -30.0f};
inline constexpr int numCells{static_cast<int>(2.0f / (kParticleRadius * 2))};
inline constexpr int maxParticlePerCell{4};
} // namespace conf
