#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_new_line(char *string) {  
  int length = strlen(string);

  if (string[length - 1] == '\n') string[length - 1] = '\0';
  if (string[length] == '\n') string[length] = '\0';
  }