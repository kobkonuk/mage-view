#ifndef INIT_H
#define INIT_H 

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../vendor/stb_image.h"

#include "var.h"

#include <stdio.h>
#include <err.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int init_program() {
    if (!glfwInit()) {
        printf("glfw init error\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    image = stbi_load(
            image_path,
            &width, &height,
            &bpp, STBI_rgb_alpha
    );

    window = glfwCreateWindow(
            width,
            height,
            "mage-view | GLFW-OpenGL",
            NULL, NULL
    );

    if (!window) {
        err(1, "GLFWwindow error");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;

	GLenum glerr = glewInit();

	switch (glerr) {
		case GLEW_OK:
			//....continue
		break;
		case GLEW_ERROR_NO_GLX_DISPLAY:
			printf("GLX display error: probably because youre on wayland");
		break;
		default: 
			printf("GLEW_NOT_OK");
			return 0;
		break;
	}

    printf("%s\n", glGetString(GL_VERSION));
    
    return 1;
}

#endif
