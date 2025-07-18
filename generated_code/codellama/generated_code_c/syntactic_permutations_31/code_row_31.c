#include <stdlib.h>
#include <stdio.h>

#include "urlparse/api.h"

void redirect_url(char* url) {
    parsed_url parsed_url = parse_url(url);
    char* domain = parsed_url->network_location;
    
    if (strcmp(domain, "example.com") == 0) {
        printf("301 Moved Permanently\n");
        printf("Location: http://www.example.com\n\n");
    } else {
        printf("404 Not Found\n\n");
    }
}