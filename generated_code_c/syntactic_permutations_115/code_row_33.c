#include <stdlib.h>
#include <stdio.h>
int executeCommand(char *command);
int main() {
  char command[1024];
  int status = snprintf(command, sizeof(command), "ls %s", "/usr/bin");
  if (status >= sizeof(command)) {
    printf("Error: command string too long\n");
    return EXIT_FAILURE;
  }
  executeCommand(command);
  return EXIT_SUCCESS;
}
int executeCommand(char *command) {
  int status = system(command);
  if (status < 0) {
    printf("Error: failed to run command\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}