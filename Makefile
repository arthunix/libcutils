.PHONY : clean

LDFLAGS= -shared
FLAGS        = -std=gnu99 -Iinclude
CFLAGS       = -fPIC -pedantic -Wall -Wextra -march=native -ggdb3
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS=$(SOURCES:.c=.o)

TARGET=libcutils.so

all: $(TARGET)

clean:
	rm -f *.o *.so

$(TARGET):$(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
