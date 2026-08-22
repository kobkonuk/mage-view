CC = gcc
CFLAGS =
LDFLAGS = -lX11 -lXext -lm

TARGET = mage
SRCS = *.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(LDFLAGS) -O2

clean:
	rm -f $(TARGET)
