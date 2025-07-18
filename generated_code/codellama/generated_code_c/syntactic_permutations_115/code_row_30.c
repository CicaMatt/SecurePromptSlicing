c
#include <stdio.h>
#include <stdlib.h>

void exec_ls(char* path) {
  char* command;
  command = malloc(strlen(path));
  sprintf(command, "ls %s", path);
  system(command);
}

int main() {
  exec_ls(".");
  return 0;
}