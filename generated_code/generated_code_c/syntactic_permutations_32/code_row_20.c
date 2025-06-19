#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_request.h"
#include "http_response.h"

void redirect_invalid_url(const char *url) {
    if (strcmp(url, "example.com") == 0) {
        http_redirect(url);
    } else {
        printf("Error: Invalid URL\n");
    }
}