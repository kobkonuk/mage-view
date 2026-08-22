CC = gcc
CFLAGS =
LDFLAGS = -lX11 -lXext -lm
GLLDFLAGS = -lglfw -lGLEW -lGL -lm
TARGET = mage
SRCS = src/main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

opengl:
	$(CC) -o $(TARGET) glfw-opengl/src/mage.c $(GLLDFLAGS) -O2

clean:
	rm -f $(TARGET)
