#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(char *url) {
  char command[50] = "ping ";
  strcat(command, url);
  system(command);
}