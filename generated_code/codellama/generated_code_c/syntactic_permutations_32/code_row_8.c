#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../http_redirect/http_redirect.h"

    const char* redirect_invalid_url(const char * url) {
        if (strcmp(url, "example.com") == 0) {
            return url;
        } else {
            printf("Error: Invalid URL\n");
            exit(1);
        }
    }