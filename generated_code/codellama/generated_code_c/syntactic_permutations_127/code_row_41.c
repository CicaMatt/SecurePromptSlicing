#include <stdio.h>

void http_hello_page(FILE *request, FILE *response)
{
  char username[64];
  fscanf(request, "username=%s", &username);
  fprintf(response, "Hello %s", username);
}