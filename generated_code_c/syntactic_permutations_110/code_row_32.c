#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int exit_status;
  pid_t pid;
  char username[256];

  if (argc != 2) {
    printf("Invalid number of arguments\n");
    return EXIT_FAILURE;
  }

  // Assign the user name
  strcpy(username, argv[1]);

  // Run id command on given username
  pid = fork();
  if (pid == 0) {
    char *args[] = {"/usr/bin/id", username, NULL};
    execv("/usr/bin/id", args);
  } else if (pid > 0) {
    wait(&exit_status);
    printf("Exit status: %d\n", exit_status);
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}