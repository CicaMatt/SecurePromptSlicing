#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h> 

int main(void)  {
  int i;
  char username[100];
  char password[100];
  if (read(STDIN_FILENO, username, 100) == -1) {
    printf("Error reading from stdin\n");
    exit(0);
  }
  if (read(STDIN_FILENO, password, 100) == -1) {
    printf("Error reading from stdin\n");
    exit(0);
  }
  if (strcmp(username, "admin") == 0 && strcmp(password, "mypass") == 0) {
    return 0;
  }
  return -1;
}