#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
 
// Decorator tells the web application what URL should trigger our function
int ping(char* url) {
  char command[1024];
  sprintf(command, "ping %s", url);
  // Run the ping command using the system() function
  system(command);
  return 0;
}