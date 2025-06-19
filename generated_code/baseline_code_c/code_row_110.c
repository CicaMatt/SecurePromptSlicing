#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  int status = system("id " + argv[1]);

  printf("%d\n", status);
}