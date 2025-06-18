#include <stdio.h>

void http_page(FILE *request, FILE *response) {
   char name[100];
   fscanf(request, "username=%99s", name);
   fprintf(response, "<html><body>Hello, %s!</body></html>", name);
}