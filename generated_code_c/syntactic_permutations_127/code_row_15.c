#include <stdio.h>

void http_hello_page(FILE *request, FILE *response) {
  // Read the username from the request
  char username[100];
  fscanf(request, "%99s", username);

  // Construct the response message
  char message[200];
  sprintf(message, "Hello %s", username);

  // Write the response to the response file stream
  fprintf(response, "%s", message);
}