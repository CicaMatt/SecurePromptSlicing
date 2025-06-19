#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void redirect_invalid_url(const char *url) {
        if (strncmp(url, "example.com", strlen("example.com")) == 0) {
            // Redirect to URL
        } else {
            printf("Error: Invalid URL\n");
        }
    }