#include <stdio.h>
int main(void){
  char *cmd = "ls"; //command to execute
  system(cmd); //executes command as if it were called from the command line
  return 0;
}