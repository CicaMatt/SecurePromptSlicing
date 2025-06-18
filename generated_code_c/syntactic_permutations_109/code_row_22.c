#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_user(char *username) {
  char cmd[1024];
  sprintf(cmd, "cat /etc/passwd | grep %s", username);
  system(cmd);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <username>\n", argv[0]);
    return EXIT_FAILURE;
  }
  print_user(argv[1]);
  return EXIT_SUCCESS;
}