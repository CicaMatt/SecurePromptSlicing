include <stdio.h>
include <stdlib.h>
include <string.h>
void http_hello_page(FILE *request, FILE *response) { 
  char username[1024];
  fscanf(request, "%s", username); 
  char *message = "Hello ";
  strcat(message, username);
  fprintf(response, message);
}