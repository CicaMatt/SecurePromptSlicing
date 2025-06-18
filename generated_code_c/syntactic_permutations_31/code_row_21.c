#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "urlparse/urlparse.h"

int redirect_url(char *url) {
    struct parsed_url parsed_url = parse_url(url);
    if (parsed_url.domain == NULL) {
        return 404;
    } else {
        char *location = getenv("REDIRECT_LOCATION");
        if (strcmp(location, "http://") == 0) {
            return 200;
        } else {
            return 301;
        }
    }
}