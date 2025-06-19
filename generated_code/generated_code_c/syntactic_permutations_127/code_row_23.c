#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response){
  //read request
  char* username = (char*)malloc(1024 * sizeof(char));
  fgets(username, 1024, request);
  //construct response
  char *hello_string = "Hello ";
  int hello_strlen = strlen(hello_string);
  int username_len = strlen(username);
  int total_len = hello_strlen + username_len;
  char* hello_username = (char*)malloc((total_len + 1) * sizeof(char));
  memset(hello_username, '\0', (total_len + 1) * sizeof(char));
  strcat(hello_username, hello_string);
  strcat(hello_username, username);
  //write response
  fprintf(response, "%s", hello_username);
}