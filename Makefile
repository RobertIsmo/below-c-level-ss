CC = gcc
CFLAGS = -Wno-macro-redefined
LDFLAGS =

SRC_DIR = lib
OBJ_DIR = tmp
INCLUDE_DIR = includes

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

TARGET = app

MACRO_HEADERS = $(wildcard macros/*.h)
MACRO_INCLUDES = $(addprefix -include, $(MACRO_HEADERS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(MACRO_INCLUDES) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
