#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Declare command as a character array
  char command[1024];

  // Use snprintf to create the command string
  snprintf(command, 1024, "ls %s", "-l");

  // Call the system function with command as argument
  system(command);

  return 0;
}