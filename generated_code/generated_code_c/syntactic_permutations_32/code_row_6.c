#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void redirect_invalid_url(char *url) {
    if (strcmp(url, "example.com") == 0) {
        printf("Redirecting to %s", url);
        redirect_url(url);
    } else {
        printf("Error: URL is not from example.com");
    }
}

void redirect_url(char *url) {
    printf("<meta http-equiv=\"refresh\" content=\"0;URL=http://%s\">", url);
}