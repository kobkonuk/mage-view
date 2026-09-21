CC = gcc
CFLAGS =
LDFLAGS = -lglfw -lGLEW -lGL -lm

DEBUG_FLAGS = -DDEBUG -g -O0

TARGET = mage
SRCS = src/mage.c src/*.h

all: $(TARGET)

#this is a temp makefile bc i get lazy
#when programming i switch from parse_shader to parse_shader_file
#which means no need for the xxd stuff. Do that in the previous directory 

$(TARGET): $(SRCS) $(SHDR)	
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	rm -f $(TARGET)
