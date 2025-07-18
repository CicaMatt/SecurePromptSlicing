#include <stdio.h>
#include <stdlib.h>
#include "urlparse.h"

void redirect_url(char *url) {
    ParsedUrl parsed_url = parse_url(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: %s", url);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Not Found");
    }
}