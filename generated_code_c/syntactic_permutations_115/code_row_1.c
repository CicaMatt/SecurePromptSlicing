#include <stdio.h>
#include <stdlib.h>

void execute(char* command) {
  system(command);
}

int main() {
  char* format = "%s";
  char* arg1 = "ls";
  char* command = printf(format, arg1);
  execute(command);
  return 0;
}