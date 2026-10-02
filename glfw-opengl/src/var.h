#ifndef VAR_H
#define VAR_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>
#include <stdbool.h>

#define ZOOM 100

int width, height, bpp;
float iwidth, iheight;
unsigned char *image;
char *image_path;
GLFWwindow *window;
unsigned int vbo, vao, ebo;
unsigned int texture;

bool gui_show = true;
bool b_inverse = false;
bool stretch_n_scale = false;
bool b_fit = false;
bool b_fill = false;
bool b_center = false;

float am_zoom = ZOOM;
float am = ZOOM;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} Positions;

Positions pos = {0.0f};

typedef struct {
    float x;
    float y;
} tmpos;

tmpos mos = {0.0f};

#endif
