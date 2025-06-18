#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "urlparse.h"
void redirect_url(char *url) {
    struct parsed_url parsed_url;
    parse_url(url, &parsed_url);
    if (strcasecmp(parsed_url.host, "example.com") == 0) {
        // redirect the url
    } else {
        // do not redirect the url
    }
}