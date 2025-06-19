#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void execute_command(char *command) {
  char buffer[1024];
  FILE *fp;
  
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    return;
  }
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);
  }
  
  pclose(fp);
}

int main() {
  char *command = "ls -l";
  execute_command(command);
  return 0;
}