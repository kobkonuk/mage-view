#ifndef MATH_H
#define MATH_H

float vertices[] = {
    // positions        colors      texcoords
    1.0f, 1.0f, 0.0f,   1,0,0,      1,1,
    1.0f, 0.0f, 0.0f,   0,1,0,      1,0,
    0.0f, 0.0f, 0.0f,   0,0,1,      0,0,
    0.0f, 1.0f, 0.0f,   1,1,0,      0,1,
};

void ortho2d(float *m, float left, float right, float bottom, float top) {
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0]  = 2.0f / (right - left);
    m[5]  = 2.0f / (bottom - top);
    m[10] = -1.0f;
    m[12] = -(right + left) / (right - left);
    m[13] = -(bottom + top) / (bottom - top);
    m[15] = 1.0f;
}

void model2d(float *m, float x, float y, float w, float h) {
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0]  = w;    // scale x
    m[5]  = h;    // scale y
    m[10] = 1.0f;
    m[12] = x;    // translate x
    m[13] = y;    // translate y
    m[15] = 1.0f;
}

#endif
