#ifndef GLBUFFERRAY_H
#define GLBUFFERRAY_H

#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include "var.h"
#include "math.h"

#include <stdbool.h>

void bind_buffers() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void unbind_buffers() { 
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool gen_and_bind_stuff() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    bind_buffers();

    glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(vertices), 
            vertices, 
            GL_STATIC_DRAW
    );

    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            sizeof(indices), 
            indices, 
            GL_STATIC_DRAW
    );

    size_t stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
   
    unbind_buffers();

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return true; // too lazy for good error checking right now mate
}

#endif
