CC = gcc
WINCC = x86_64-w64-mingw32-gcc

CFLAGS =
LDFLAGS = -lX11 -lXext -lm

GLLDFLAGS = -lglfw -lGLEW -lGL -lm
MINGW_FLAGS = -lglfw3 -lglew32 -lopengl32 -lgdi32 -static -static-libgcc -DGLEW_STATIC
WIN_CFLAGS = -Ivendor/windows/GLEW/include -Ivendor/windows/GLFW/include -static -static-libgcc -DGLEW_STATIC
WIN_LDFLAGS = -Lvendor/windows/GLEW/lib -Lvendor/windows/GLFW/lib
WIN_LIBS = -lglfw3 -lglew32 -lopengl32 -lgdi32

TARGET = mage
WIN_TARGET = mage.exe

SRCS = x11/src/main.c

SHADER_SRC = glfw-opengl/res/shaders/shader.glsl
SHADER_HDR = glfw-opengl/src/glsl.h

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

opengl:
	xxd -i $(SHADER_SRC) > $(SHADER_HDR)
	$(CC) -o $(TARGET) glfw-opengl/src/mage.c $(GLLDFLAGS) -O2

opengl-win:
	xxd -i $(SHADER_SRC) > $(SHADER_HDR)
	$(CC) -o $(WIN_TARGET) glfw-opengl/src/mage.c $(WIN_CFLAGS) $(WIN_LDFLAGS) $(WIN_LIBS) -O2

clean:
	rm -f $(TARGET) $(SHADER_HDR)

.PHONY: all opengl clean
