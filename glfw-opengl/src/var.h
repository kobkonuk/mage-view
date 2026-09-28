#ifndef VAR_H
#define VAR_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <stdbool.h>

int width, height, bpp;
int iwidth, iheight;
unsigned char *image;
char *image_path;
GLFWwindow *window;
unsigned int vbo, vao, ebo;
unsigned int texture;

bool gui_show = true;
int gui_pos = 50;
bool b_inverse = false;
bool stretch_n_scale = false;


float am_zoom = 10;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} ZoomDimensions;

ZoomDimensions zoom = {0.0f};

#endif
