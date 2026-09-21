CC = gcc
CFLAGS =
LDFLAGS = -lX11 -lXext -lm
GLLDFLAGS = -lglfw -lGLEW -lGL -lm
TARGET = mage
SRCS = src/main.c

SHADER_SRC = res/shaders/shader.glsl
SHADER_HDR = src/glsl.h

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

$(SHADER_HDR): $(SHADER_SRC)
	xxd -i $(SHADER_SRC) > $(SHADER_HDR)

opengl: 
	$(CC) -o $(TARGET) glfw-opengl/src/mage.c $(GLLDFLAGS) -O2

clean:
	rm -f $(TARGET)

.PHONY: all opengl clean
