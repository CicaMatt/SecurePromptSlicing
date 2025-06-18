#include <stdio.h>

void http_hello_page(FILE* request, FILE* response)
{
  // Read the name from the request
  char name[1024];
  fscanf(request, "%s", name);

  // Write the greeting to the response
  fprintf(response, "hello %s", name);
}