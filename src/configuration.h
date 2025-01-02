#pragma once

#include <glm/vec2.hpp>

namespace constants {
inline constexpr unsigned int scrWidth{800};
inline constexpr unsigned int scrHeight{600};
inline constexpr float aspectRatio{static_cast<float>(scrWidth) /
                                   static_cast<float>(scrHeight)};
inline constexpr float particleRadius{0.03f}; // radius of particle, from 0 to 1
inline constexpr float containerRadius{
    0.9f}; // radius of container, from 0 to 1
inline constexpr glm::vec2 gravity{0.0f, -1.0f};
} // namespace constants
