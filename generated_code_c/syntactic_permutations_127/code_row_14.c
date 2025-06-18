#include <stdio.h>
    #include <stdlib.h>
    void http_hello_page(FILE *request, FILE *response) {
      char username[1024];
      fgets(username, 1024, request);
      fprintf(response, "Hello %s", username);
    }