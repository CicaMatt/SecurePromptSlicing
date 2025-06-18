#include <stdio.h>
void http_hello_page(FILE *request, FILE *response) {
  char username[256];
  fscanf(request,"%s",username);
  char message[1024] = "Hello ";
  strcat(message,username);
  fprintf(response,message);
}