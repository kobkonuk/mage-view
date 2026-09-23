#ifndef VAR_H
#define VAR_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int width, height, bpp;
unsigned char *image;
char *image_path;
GLFWwindow *window;
unsigned int vbo, vao, ebo;
unsigned int texture;
_Bool b_inverse = 0;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} ZoomDimensions;

ZoomDimensions zoom = {0.0f};

#endif
