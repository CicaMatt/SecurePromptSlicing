#include <stdio.h>

void http_hello_page(FILE* request, FILE* response) {
  char username[30];
  fscanf(request, "username = %29s", username);
  fprintf(response, "Hello, %s!", username);
}