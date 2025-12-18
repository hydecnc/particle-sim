#pragma once

#include <glm/glm.hpp>

namespace conf {
inline constexpr unsigned int kWidth{800};
inline constexpr unsigned int kHeight{600};
inline constexpr glm::vec4 kBackgroundColor{0.1f, 0.1f, 0.1f, 1.0f};
inline constexpr float aspectRatio{static_cast<float>(kWidth) /
                                   static_cast<float>(kHeight)};
inline constexpr float kParticleRadius{10.0f};
inline constexpr int kParticleSpawnRate{5};
inline constexpr int kMaxParticles{3000};
inline constexpr float kContainerRadius{
    0.9f}; // radius of container, from 0 to 1
inline constexpr glm::vec2 gravity{0.0f, -30.0f};
inline constexpr glm::vec2 acceleration{1.0f, -30.0f};
inline constexpr int kNumCells{10};
inline constexpr int maxParticlePerCell{4};
// Colors
inline constexpr glm::vec4 skyBlue{79.0f / 255.0f, 195.0f / 255.0f,
                                   247.0f / 255.0f, 1.0f};
} // namespace conf
