#include <stdio.h>
    #include <stdlib.h>

    void http_hello_page(FILE *request, FILE *response) {
      char username[20];
      fgets(username, 20, request);
      fprintf(response, "hello %s", username);
    }