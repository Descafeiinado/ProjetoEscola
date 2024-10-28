# all: main

# CC = clang
# override CFLAGS += -g -Wno-everything -pthread -lm

# SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
# HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

# main: $(SRCS) $(HEADERS)
# 	$(CC) $(CFLAGS) $(SRCS) -o "$@"

# main-debug: $(SRCS) $(HEADERS)
# 	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

# clean:
# 	rm -f main main-debug

all: main

CC = gcc
override CFLAGS = -IC://msys64/mingw64/include -LC://msys64/mingw64/lib -g -Wno-everything -pthread -lm -fexec-charset=UTF-8 -finput-charset=UTF-8

SRCS = $(shell dir /s /b *.c)
HEADERS = $(shell dir /s /b *.h)
main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@.exe"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@.exe"

clean:
	del /f main.exe main-debug.exe