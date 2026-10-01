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
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        stretch_n_scale = true;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        am_zoom += 20; // zoom in
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        am_zoom -= 20; // zoom out
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mos.y -= 20;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mos.y += 20;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mos.x += 20;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS  ||
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mos.x -= 20;
    }
}

#endif
