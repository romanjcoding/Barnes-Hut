#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <vector>
#include "body.h"
#include <vector>

struct Renderer {
    Renderer(int w, int h, const char* title) {
        if (!glfwInit()) {
            throw std::runtime_error("glfwInit failed.");
        }
        m_window = glfwCreateWindow(w, h, title, nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }
        glfwMakeContextCurrent(m_window);
        glPointSize(2.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    ~Renderer() {
        if (m_window) glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool should_close() const { return glfwWindowShouldClose(m_window); }

    void render(const std::vector<Body>& bodies) {
        glBegin(GL_POINTS);
        for (const Body& body : bodies) { 
            glVertex2f(body.m_position[0], body.m_position[1]); 
        }
        glEnd();
    }

    void begin_frame() {
        int fbw = 0, fbh = 0;
        glfwGetFramebufferSize(m_window, &fbw, &fbh);
        glViewport(0, 0, fbw, fbh);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void end_frame() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

private:
    GLFWwindow* m_window{nullptr};
};
