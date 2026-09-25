#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include "cli.h"
#include "shader.h"
#include "math.h"
#include "glsl.h"
#include "var.h"
#include "init.h"
#include "gui.h"
#include "glbufferray.h"

int program(int argc, char *argv[]) 
{
    image_path = argv[1];
    if (!image_lowk_valid(image_path, argc)) {
        return 0;
    }

    if (!init_program()) {
        return 0;
    }

#ifndef DEBUG
    shader_program_source shader_source = parse_shader(
            (const char*)glfw_opengl_res_shaders_shader_glsl
    );
#endif

#ifdef DEBUG
    shader_program_source shader_source = parse_shader_file(
            "res/shaders/shader.glsl"
    ); 
    // use parse_shader_file when debugging 
    // no need to wait for compiling when editing shader.glsl
#endif

    unsigned int shader = create_shader(
            shader_source.vertexShader, 
            shader_source.fragmentShader
    );

    gen_and_bind_stuff();

    glUseProgram(shader);
    glBindVertexArray(vao);

    GLint loc = glGetUniformLocation(shader, "u_Texture");
    glUniform1i(loc, 0);

    float projection[16];
    ortho2d(projection, 0.0f, (float)width, 0.0f, (float)height);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, projection);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    init_gui();
	
    while (!glfwWindowShouldClose(window)) 
    {
		glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            b_inverse = true; // not a toggle... but you hold it in... epic
        }

		glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        float model[16];
        model2d(model, zoom.x, zoom.y, width+zoom.w, height+zoom.h);
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model);
        glUniform1i(glGetUniformLocation(shader, "b_inverse"), b_inverse);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        draw_gui_setup();
        sure_draw_gui();

		glfwSwapBuffers(window);
	}
    gui_shutdown();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
	glDeleteProgram(shader);

    stbi_image_free(image);

	glfwTerminate();
	return 1;
}

#ifdef __linux__
int main(int argc, char *argv[]) {
	if (!program(argc, argv)) {
		return 1;
	}
	return 0;
}
#endif

#ifdef _WIN32
int WinMain(int argc, char *argv[]) {
	if (!program(argc, argv)) {
		return 1;
	}
	return 0;
}
#endif
