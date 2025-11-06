#pragma once
#include <array>

struct Body {
    std::array<float, 2> m_position{};
    std::array<float, 2> m_velocity{};
    std::array<float, 2> m_acceleration{};
    float m_mass{1.0f};
    float m_radius{};
    void update(float dt) {
        m_velocity[0] += m_acceleration[0] * dt;
        m_velocity[1] += m_acceleration[1] * dt;

        m_position[0] += m_velocity[0] * dt;
        m_position[1] += m_velocity[1] * dt;
    }

};