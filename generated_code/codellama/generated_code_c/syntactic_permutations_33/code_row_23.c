#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_redirect"

/* Redirects invalid URLs */
int redirect_invalid_url(char *url) {
  if (strstr(url, "example.com") != NULL) {
    char *new_url = malloc(sizeof(char) * strlen("https://www.example.com"));
    sprintf(new_url, "https://www.example.com");
    http_redirect(new_url);
  } else {
    printf("Error: Invalid URL\n");
  }
}