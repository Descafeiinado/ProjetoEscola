rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

all: main
CC = clang

ifeq ($(OS), Windows_NT)
    CC := "gcc"
    override CFLAGS += -I./ -o
else
    override CFLAGS += -g -Wno-everything -pthread -lm
endif

SRCS = $(call rwildcard,.,*.c)
HEADERS = $(call rwildcard,.,*.h)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug