#ifndef INPUT_H
#define INPUT_H

#include "var.h"
#include <stdbool.h>

void input_magic(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            b_inverse = true; // not a toggle... but you hold it in... epic
        }
        
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (stretch_n_scale) stretch_n_scale = false;
            else stretch_n_scale = true;
        }
        
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			gui_pos -= 10;
        }

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            zoom.x -= am_zoom;
            zoom.y -= am_zoom;

            zoom.w += am_zoom;
            zoom.h += am_zoom;
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            zoom.x += am_zoom;
            zoom.y += am_zoom;

            zoom.w -= am_zoom;
            zoom.h -= am_zoom;
        }
}

#endif
