CC = gcc
CFLAGS =
LDFLAGS = -lglfw -lGLEW -lGL -lm

TARGET = mage
SRCS = src/mage.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

clean:
	rm -f $(TARGET)
