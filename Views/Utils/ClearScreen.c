#include <stdio.h>

void clear_screen() {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

  puts(CLEAR_SCREEN_ANSI);
}