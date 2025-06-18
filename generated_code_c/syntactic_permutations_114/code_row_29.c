#include <stdio.h>
#include <stdlib.h>

int main() {
  char *cmd;
  int status;
  cmd = "ls";
  status = system(cmd);
  printf("%s\n",cmd);
  return 0;
}