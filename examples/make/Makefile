# This is comment
CC=cl
CFLAGS=/c
EXECUTABLE=foo
SOURCES=main.cpp sqr.cpp hello.cpp
OBJECTS=$(SOURCES:.cpp=.obj)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) /Fe: $@ $(OBJECTS)

.cpp.obj:
	$(CC) /Fe: $@ $(CFLAGS) $<

clean:
	del *.obj *.exe