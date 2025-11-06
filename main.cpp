#include "body.h"
#include "renderer.h"
#include "simulation.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <random>
#include <iostream>

int main(void)
{
    constexpr size_t num_bodies { 5000 };
    float dt                    { 0.00001f };
    Simulation sim              { num_bodies, dt };
    Renderer renderer           { 640, 480, "Barnes-Hut Simulation" };

    while (!renderer.should_close()) {
        sim.update();
        renderer.begin_frame();
        renderer.render(sim.m_bodies);
        renderer.end_frame();
    }
    return 0;
}