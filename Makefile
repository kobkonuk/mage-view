CC = gcc
CFLAGS =
LDFLAGS = -lX11 -lXext -lm
GLLDFLAGS = -lglfw -lGLEW -lGL -lm
TARGET = mage
SRCS = x11/src/main.c

SHADER_SRC = glfw-opengl/res/shaders/shader.glsl
SHADER_HDR = glfw-opengl/src/glsl.h

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

opengl:
	xxd -i $(SHADER_SRC) > $(SHADER_HDR)
	$(CC) -o $(TARGET) glfw-opengl/src/mage.c $(GLLDFLAGS) -O2

clean:
	rm -f $(TARGET) $(SHADER_HDR)

.PHONY: all opengl clean
