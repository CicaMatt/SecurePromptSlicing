#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int bufsize = atoi(argv[1]);
  char *buf;

  if (!bufsize) {
    printf("Please specify a positive integer\n");
    return -1;
  }

  buf = (char *)malloc(sizeof(char)*bufsize);
  if (!buf) {
    printf("Buffer allocation failed\n");
    return -1;
  }

  memset(buf, '*', bufsize-1);
  buf[bufsize-1] = '\0';

  printf("%s\n", buf);

  free(buf);

  return 0;
}