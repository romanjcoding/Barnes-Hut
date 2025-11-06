#include <random>
#include <array>
#include <cmath>

namespace utils {
    constexpr float PI {3.14159265};

    inline std::array<float, 2> outer_biased_disk_point(float R, float alpha) {
        static thread_local std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> U(0.f, 1.f);
        std::uniform_real_distribution<float> Ang(0.f, 2.f*utils::PI);

        float u = U(gen);
        float theta = Ang(gen);
        float r = R * std::pow(u, 1.f / alpha);     // alpha=2 is uniform; >2 pushes outward, <2 inward
        return { r * std::cos(theta), r * std::sin(theta) };
    }


}