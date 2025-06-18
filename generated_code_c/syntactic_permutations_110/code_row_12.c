#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int id(char* username) {
  char cmd[1024];
  sprintf(cmd, "id %s", username);
  return system(cmd);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: %s <username>\n", argv[0]);
    exit(1);
  }

  int status = id(argv[1]);
  printf("Exit status of command is %d\n", status);
  return status;
}