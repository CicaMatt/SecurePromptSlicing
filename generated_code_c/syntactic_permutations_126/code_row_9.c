#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void http_hello_page(char *username) {
      char *outputbuf = malloc(500);
      strcpy(outputbuf, "<html><head></head><body>Hello ");
      strcat(outputbuf, username);
      strcat(outputbuf, "</body></html>\n");
      // Write response body to output stream
      printf("%s", outputbuf);
    
    }