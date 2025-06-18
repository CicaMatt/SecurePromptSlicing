#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>
int main() {
  char *url = getenv("URL");
  if (url == NULL) {
      printf("No URL specified\n");
      exit(1);
  }
  int status;
  char command[256];
  memset(command, '\0', sizeof(command));
  strcat(command,"ping ");
  strcat(command,url);
  status = system(command);
  if (status == 0) {
      printf("URL is alive\n");
  } else {
      printf("URL is not alive\n");
  }
}