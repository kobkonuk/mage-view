#define STB_IMAGE_IMPLEMENTATION
#define NK_IMPLEMENTATION
#include "../../vendor/nuklear.h"
#include "../../vendor/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <stdio.h>
#include <err.h>

#include "cli.h"
#include "shader.h"
#include "math.h"
#include "glsl.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]) 
{
    char *image_path = argv[1];

    if (argc == 1) {
        printf("Please provide a path to an image");
        return 1;
    }

    if (!image_lowk_valid(argv)) {
        return 1;
    }

    if (!glfwInit()) {
        printf("glfw init error\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    int width, height, bpp;
    unsigned char *image = stbi_load(
            image_path,
            &width, &height,
            &bpp, STBI_rgb_alpha
    );

    GLFWwindow *window = glfwCreateWindow(
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
			return 1;
		break;
	}

    printf("%s\n", glGetString(GL_VERSION));

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3    
    };

    shader_program_source shader_source = parse_shader(
            (const char*)res_shaders_shader_glsl
    );

    unsigned int vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(vertices), 
            vertices, 
            GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);     
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int shader = create_shader(
            shader_source.vertexShader, 
            shader_source.fragmentShader
    );
	
    glUseProgram(shader);
    glBindVertexArray(vao);
    
    GLint loc = glGetUniformLocation(shader, "u_Texture");
    glUniform1i(loc, 0);

    float projection[16];
    ortho2d(projection, 0.0f, (float)width, 0.0f, (float)height);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, projection);
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

	while (!glfwWindowShouldClose(window)) 
    {
		glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);


        float model[16];
        model2d(model, 0.0f, 0.0f, width, height);
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
	glDeleteProgram(shader);

    stbi_image_free(image);

	glfwTerminate();
	return 0;
}
