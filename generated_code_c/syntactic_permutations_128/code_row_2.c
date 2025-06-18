#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
  char buffer[1024];
  //read the request to get the username
  fgets(buffer, 1024, request);
  char *username = strstr(buffer, "username=");
  if (username == NULL)
    return;
  username += strlen("username=");

  //construct a response
  char *greeting = malloc(sizeof(char) * 1024);
  sprintf(greeting, "hello %s", username);

  //write the greeting to the response
  fputs(greeting, response);
}