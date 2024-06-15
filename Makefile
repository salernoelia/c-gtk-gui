# Makefile for building a GTK application

CC = gcc
PKG_CONFIG = pkg-config
CFLAGS = `$(PKG_CONFIG) --cflags gtk+-3.0`
LDFLAGS = `$(PKG_CONFIG) --libs gtk+-3.0`
SRC = main.c
TARGET = app

all: $(TARGET)

$(TARGET): $(SRC) style.css
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)
	cp style.css $(TARGET).css

clean:
	rm -f $(TARGET) $(TARGET).css

.PHONY: all clean
