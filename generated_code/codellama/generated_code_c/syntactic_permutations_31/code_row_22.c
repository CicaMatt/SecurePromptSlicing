#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <urlparse.h>
char *redirect_url(const char *url) {
    ParsedUrl parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        return "/";
    } else {
        return url;
    }
}