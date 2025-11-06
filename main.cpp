#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <random>
#include <iostream>

struct Point {
    float mass{1e-9f};
    float x{0.0f};
    float y{0.0f};
    float velocity_x{0.0f};
    float velocity_y{0.0f};
    float acc_x{0.0f};
    float acc_y{0.0f};
};

std::vector<Point> generate_points(int num_points) {
    std::vector<Point> points (num_points);
    for (Point& point : points) {
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        x = 2 * (x - 0.5f);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        y = 2 * (y - 0.5f);

        float velocity_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        velocity_x = 0.0005 * (velocity_x - 0.5f);

        float velocity_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        velocity_y = 0.0005 * (velocity_y - 0.5f);

        point.x = x;
        point.y = y;
        point.velocity_x = velocity_x;
        point.velocity_y = velocity_y;
    }
    return points;
}

void update_positions(std::vector<Point>& points) {
    for (Point& point : points) {
        point.x += point.velocity_x;
        point.y += point.velocity_y;
    }
}

void update_velocities(std::vector<Point>& points) {
    for (Point& point : points) {
        point.velocity_x += point.acc_x;
        point.velocity_y += point.acc_y;
    }
}

void update_accelerations(std::vector<Point>& points) {

    for (auto& p : points) { p.acc_x = 0.0f; p.acc_y = 0.0f; }

    constexpr float eps2 = 1e-6f;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < points.size(); j++) {
            if (i == j) continue;

            float dx = points[j].x - points[i].x;
            float dy = points[j].y - points[i].y;

            float r2 = dx*dx + dy*dy + eps2;
            float inv_r = 1.0f / std::sqrt(r2);
            float inv_r3 = inv_r * inv_r * inv_r;

            points[i].acc_x += points[j].mass * dx * inv_r3;
            points[i].acc_y += points[j].mass * dy * inv_r3;
        }
    }
}


void render_points(const std::vector<Point>& points) {
    glBegin(GL_POINTS);
    for (Point point : points) { glVertex2f(point.x, point.y); }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Barnes-Hut Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    constexpr int num_points  { 10000 };
    std::vector<Point> points { generate_points(num_points) };
    glfwMakeContextCurrent(window);
    glPointSize(2.0f);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        update_accelerations(points);
        update_velocities(points);
        update_positions(points);
        render_points(points);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}