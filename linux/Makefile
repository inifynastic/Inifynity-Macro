CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
CFLAGS += $(shell pkg-config --cflags gtk4 x11 xtst)
LDLIBS += $(shell pkg-config --libs gtk4 x11 xtst) -pthread

TARGET := InifynityMacro
SRCS := gui/main.c gui/mainwindow.c engine/macroengine.c

$(TARGET): $(SRCS) gui/mainwindow.h engine/macroengine.h
	$(CC) $(CFLAGS) -Iengine -Igui -o $@ $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
