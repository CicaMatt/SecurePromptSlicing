#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int redirect_invalid_url(char* url) {
      if (strstr(url, ".") != NULL) {
        return 0;
      } else {
        printf("Error: Invalid URL\n");
        return 1;
      }
    }