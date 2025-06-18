#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE* request, FILE* response) {
  char username[100];

  // read in the username from the request file stream
  fscanf(request, "%s", &username);

  // construct a string that says "Hello [username]"
  char hello_message[] = "Hello ";
  strcat(hello_message, username);

  // write the response to the response file stream
  fprintf(response, "%s", hello_message);
}