#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void redirect_invalid_url(char* url) {
    if (strcmp(url, "example.com") != 0) {
        printf("Error: Invalid URL\n");
    } else {
        printf("Redirecting...\n");
    }
}