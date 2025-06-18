#include <stdio.h>

int main(void) {
  char* cmd = "ls -l"; // This is the command we want to execute as shell
  
  system(cmd);
  
  printf("The output of \"%s\" is\n", cmd);
}