#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <stdio.h>
#include <err.h>

// Not gonna do SDL3 this time because SDL3 is too bloated for smaller stuff
// im only using it for games and cross platform stuff
// im not planning to port this shit to windows lol

static unsigned int CompileShader(unsigned int type, const char *source) {
	unsigned int id = glCreateShader(type);

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

        printf("Failed to compile %s shader\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment");

		printf("%s", message);

		glDeleteShader(id);
        free(message);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const char *vertexShader, const char *fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

typedef enum {
    SHADER_NONE = -1,
    SHADER_VERTEX = 0,
    SHADER_FRAGMENT = 1
} shader_type;

typedef struct {
    char vertexShader[512];
    char fragmentShader[512];
} shader_program_source;

shader_program_source parse_shader(const char* shader_path) {
    FILE *stream = fopen(shader_path, "r");

    shader_program_source source = {0};

    char line[512];
    shader_type type = SHADER_NONE;

    while (fgets(line, sizeof(line), stream)) {
        if (strstr(line, "#shader")) {
            if (strstr(line, "#vertex")) {
                type = SHADER_VERTEX;
            }
            else if (strstr(line, "fragment")) {
                type = SHADER_FRAGMENT;
            }
        }
      
        else {
            switch (type) {
                case SHADER_VERTEX:
                    strcat(source.vertexShader, line);
                break;
                case SHADER_FRAGMENT:
                    strcat(source.fragmentShader, line);
                break;
                case SHADER_NONE:
                    //printf("hello world... or i mean... hello ERROR!!");
                break;
            }
        }
    } 

    fclose(stream);
    return source;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

typedef struct {	
	const char *jpg;
	const char *jpeg;
	const char *png;
} Filetype;

Filetype filetype = {
	.jpg  = ".jpg",
	.jpeg = ".jpeg",
	.png  = ".png"
};

const char *GetFileType(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(dot) return dot;
	else err(1, "Invalid filetype. Try something called an 'image'");
}

int main(int argc, char *argv[]) 
{
    char *image_path = argv[1];

    if (argc == 1) {
		err(1, "Please provide a filepath to your desired image");
	}

	const char *type = GetFileType(argv[1]);

	if (strcmp(type, filetype.jpg) == 0);
	else if (strcmp(type, filetype.jpeg) == 0);
	else if (strcmp(type, filetype.png) == 0);
	else err(1, "Invalid filetype. Only JPEGs and PNGs are supported");

    if (!glfwInit()) {
        err(1, "glfwInit error");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // sorry for the inconsistent variable naming
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

    if (glewInit() != GLEW_OK) {
        err(1, "GLEW_NOT_OK");
        glfwTerminate();
    }
    
    printf("%s\n", glGetString(GL_VERSION));

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    shader_program_source shader_source = parse_shader(
            "res/shaders/shader.glsl"
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

	unsigned int shader = CreateShader(
            shader_source.vertexShader, 
            shader_source.fragmentShader
    );
	
    glUseProgram(shader);
    glBindVertexArray(vao);
    
    GLint loc = glGetUniformLocation(shader, "u_Texture");
    glUniform1i(loc, 0);
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
	glDeleteProgram(shader);

    stbi_image_free(image);

	glfwTerminate();
    printf("exit success");
	return 0;
}
