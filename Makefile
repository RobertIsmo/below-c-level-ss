CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -H
LDFLAGS = 

ENTRY_POINTS = app
INCLUDES = includes
LIBS = lib
MACROS = macros

BUILDS = builds
OBJS = temp

MACRO_HEADERS = $(wildcard $(MACROS)/*.h)
MACRO_INCLUDES = $(addprefix -include ,$(MACRO_HEADERS))
HEADERS = $(wildcard $(INCLUDES)/*.h)
HEADER_INCLUDES = $(addprefix -include ,$(HEADERS))

APPS = $(wildcard $(ENTRY_POINTS)/*.c)
SOURCES = $(wildcard $(LIBS)/*.c)

APP_NAMES = $(basename $(notdir $(APPS)))
SOURCE_NAMES = $(basename $(notdir $(SOURCES)))

SOURCE_OBJECTS = $(addsuffix .o,$(addprefix $(OBJS)/,$(SOURCE_NAMES)))

all: folder $(SOURCE_NAMES) $(APP_NAMES) clean

$(APP_NAMES): $(SOURCE_NAMES)
	@$(CC) $(CFLAGS) $(MACRO_INCLUDES) $(HEADER_INCLUDES) -c $(ENTRY_POINTS)/$@.c -o $(OBJS)/$@.o
	@$(CC) $(LDFLAGS) $(SOURCE_OBJECTS) $(OBJS)/$@.o -o $(BUILDS)/$@

$(SOURCE_NAMES):
	@$(CC) $(CFLAGS) $(MACRO_INCLUDES) $(HEADER_INCLUDES) -c $(LIBS)/$@.c -o $(OBJS)/$@.o

folder:
	@mkdir -p $(OBJS)
	@mkdir -p $(BUILDS)

clean:
	builds/test
	@echo finished building $(APP_NAMES)