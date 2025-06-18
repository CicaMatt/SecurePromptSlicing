#include <stdio.h>

void http_hello_page(FILE* request, FILE* response){
  char name[256];
  fgets(name, 256, request);
  fprintf(response, "Hello %s", name);
}