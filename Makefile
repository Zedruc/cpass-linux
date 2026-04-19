PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin

SRC_DIR := src
SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES := $(SRC_FILES:.c=.o)

TARGET := cpass

CC := gcc

# Default (production) flags
CFLAGS := -O2 -DNDEBUG -Wall -Wextra

# --- Build rules ---
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Targets ---
.PHONY: all dev clean install uninstall

all: $(TARGET)

# Dev build overrides CFLAGS
dev: CFLAGS := -g -O0 -Wall -Wextra
dev: clean $(TARGET)

clean:
	rm -f $(OBJ_FILES) $(TARGET)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	chmod 755 $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)