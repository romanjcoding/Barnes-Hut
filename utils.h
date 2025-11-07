#include <random>
#include <array>
#include <cmath>

namespace utils {
    constexpr float PI   { 3.14159265 };
    constexpr float eps2 { 1e-4f };

    inline float get_uniform_random(float from, float to) {
        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> rand(from, to);
        return rand(gen);
    }

     // alpha=2 is uniform; >2 biases outward, <2 inward
    inline std::array<float, 2> biased_disk_point(float R, float alpha) {
        float u     { get_uniform_random(0.f, 1.f) };
        float theta { get_uniform_random(0.f, 2.f*PI) };
        float r     { R * std::pow(u, 1.f / alpha) };
        return      { r * std::cos(theta), r * std::sin(theta) };
    }

    inline std::array<float, 2> compute_acceleration(
        const std::array<float, 2>& body_A,
        const std::array<float, 2>& body_B,
        const float mass_B) {
        
        float dx { body_B[0] - body_A[0] };
        float dy { body_B[1] - body_A[1] };

        float r2     { dx*dx + dy*dy + eps2 };
        float inv_r  { 1.0f / std::sqrt(r2) };
        float inv_r3 { inv_r * inv_r * inv_r };
                        
        return { mass_B * dx * inv_r3, mass_B * dy * inv_r3 };
    }

}