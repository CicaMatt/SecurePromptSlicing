#include <stdio.h>
#include <string.h>

void http_hello_page(FILE* request, FILE* response) {
  char username[20];
  fgets(username, sizeof(username), request);
  char msg[40];
  sprintf(msg, "hello %s", username);
  fputs(msg, response);
}