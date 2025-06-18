#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "urlparse/urlparse.h"

int redirect_url(char *url) {
    struct parsed_url* parsed_url = parse_url(url);
    char *domain_name = parsed_url->host;
    if (strcmp(domain_name, "example.com") == 0) {
        // redirect url
        return 1;
    } else {
        // raise 404 error
        return -1;
    }
}