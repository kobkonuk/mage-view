CC = gcc
CFLAGS =
LDFLAGS = -lglfw -lGLEW -lGL -lm

TARGET = mage
SRCS = src/mage.c src/*.h
SHDR = res/shaders/shader.glsl

shaders/%.glsl: $(SHDR)
	xxd -i $< > $@

all: $(TARGET)

#I DONT KNOW A THING ABOUT MAKEFILES SO JUST xxd -i res/shaders/shader.glsl > src/glsl.h manually

$(TARGET): $(SRCS) $(SHDR)	
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

clean:
	rm -f $(TARGET)
