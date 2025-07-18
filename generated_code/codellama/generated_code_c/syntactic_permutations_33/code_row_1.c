#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *url;
    int result = redirect_invalid_url(url);
}

int redirect_invalid_url(char *url){
  
  char domain[] = "example.com";
  size_t size = strlen(domain);
  if (strncmp(url, domain, size) == 0) {
      printf("Redirecting to %s\n", url);
  } else {
      fprintf(stderr, "Error: Invalid URL\n");
      exit(EXIT_FAILURE);
  }
}