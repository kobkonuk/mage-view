#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int compile_shader(unsigned int type, const char *source) {
	unsigned int id = glCreateShader(type);

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)malloc(length * sizeof(char)); // i dont like heap allocations a lot but whatever
		glGetShaderInfoLog(id, length, &length, message);

        printf("Failed to compile %s shader\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment");

		printf("%s", message); // w for debugging

		glDeleteShader(id);
        free(message);
		return 0;
	}

	return id;
}

static unsigned int create_shader(const char *vertexShader, const char *fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

typedef enum {
    SHADER_NONE,
    SHADER_VERTEX,
    SHADER_FRAGMENT
} shader_type;

typedef struct {
    char vertexShader[512];
    char fragmentShader[512];
} shader_program_source;

shader_program_source parse_shader(const char *source) {
    shader_program_source result = {0};
    shader_type type = SHADER_NONE;

    char buffer[4096];
    strncpy(buffer, source, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *line = strtok(buffer, "\n");

    while (line != NULL) {
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
                    strcat(result.vertexShader, line);
                    strcat(result.vertexShader, "\n");
                break;
                case SHADER_FRAGMENT:
                    strcat(result.fragmentShader, line);
                    strcat(result.fragmentShader, "\n");
                break;
                case SHADER_NONE:
                    printf("ill take this memory.... and PARSE IT!!! *nothing was parsed");
                break;
            }
        }
        line = strtok(NULL, "\n");
    }

    return result;
}

shader_program_source parse_shader_file(const char* shader_path) {
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
                    printf("hello world... or i mean... hello ERROR!!");
                break;
            }
        }
    }

    fclose(stream);
    return source;
}

#endif
