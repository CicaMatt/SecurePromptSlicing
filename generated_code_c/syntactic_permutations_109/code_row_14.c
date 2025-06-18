#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage %s <username> \n", argv[0]);
    exit(1);
  }
  system("cat /etc/passwd | grep username");
  return 0;
}