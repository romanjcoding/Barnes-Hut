#pragma once
#include "body.h"
#include <cstdint>
#include <vector>

struct Simulation {
    std::vector<Body> m_bodies;
    float m_dt;
    uint32_t m_frame;

    Simulation(size_t num_bodies, float dt) {
        m_bodies = generate_points(num_bodies);
        m_dt = dt;
        m_frame = 0;
    }

    std::vector<Body> generate_points(int num_bodies) {
        std::vector<Body> bodies (num_bodies);
        for (Body& body : bodies) {
            float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            x = 2 * (x - 0.5f);
            float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            y = 2 * (y - 0.5f);

            float velocity_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            velocity_x = 0.0005 * (velocity_x - 0.5f);

            float velocity_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            velocity_y = 0.0005 * (velocity_y - 0.5f);

            body.m_position[0] = x;
            body.m_position[1] = y;
            body.m_velocity[0] = velocity_x;
            body.m_velocity[1] = velocity_y;
        }
        return bodies;
    }

    void update_acceleration() {
        constexpr float eps2 = 1e-6f;
        for (size_t i = 0; i < m_bodies.size(); i++) {
            float ax { 0.0f };
            float ay { 0.0f };
            for (size_t j = 0; j < m_bodies.size(); j++) {
                if (i == j) continue;

                float dx = m_bodies[j].m_position[0] - m_bodies[i].m_position[0];
                float dy = m_bodies[j].m_position[1] - m_bodies[i].m_position[1];

                float r2 = dx*dx + dy*dy + eps2;
                float inv_r = 1.0f / std::sqrt(r2);
                float inv_r3 = inv_r * inv_r * inv_r;
                                
                ax += m_bodies[j].m_mass * dx * inv_r3;
                ay += m_bodies[j].m_mass * dy * inv_r3;
            }
            m_bodies[i].m_acceleration[0] = ax;
            m_bodies[i].m_acceleration[1] = ay;
        }
    }

    void update() {
        update_acceleration();
        for (Body& body : m_bodies) {
            body.update(m_dt);
        }
    }

};