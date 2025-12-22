#pragma once

#include <glm/glm.hpp>

namespace conf {
inline constexpr unsigned int kWidth{800};
inline constexpr unsigned int kHeight{600};
inline constexpr glm::vec4 kBackgroundColor{0.1f, 0.1f, 0.1f, 1.0f};
inline constexpr int kSubsteps{8};
inline constexpr float kAspectRatio{static_cast<float>(kWidth) /
                                    static_cast<float>(kHeight)};
inline constexpr float kParticleRadius{20.0f};
inline constexpr glm::vec4 kParticleColor{234.0f / 255.0f, 224.0f / 255.0f,
                                          200.0f / 255.0f, 1.0f};
inline constexpr int kParticleSpawnRate{20};
inline constexpr int kMaxParticles{3000};
// Radius of container, from 0 to 1
inline constexpr float kContainerRadius{0.9f};
inline constexpr glm::vec2 kGravity{0.0f, -9.8f};
inline constexpr glm::vec2 kInitalAcceleration{-60.0f * kSubsteps,
                                               -20.0f * kSubsteps};
inline constexpr int kNumCells{static_cast<int>(kWidth / kParticleRadius)};
// Colors
inline constexpr glm::vec4 skyBlue{79.0f / 255.0f, 195.0f / 255.0f,
                                   247.0f / 255.0f, 1.0f};
} // namespace conf
