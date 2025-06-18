#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int status;
  if (argc != 2) {
    printf("No username provided\n");
    exit(1);
  }
  status = system("id $1");
  printf("%d", status);
  return 0;
}