#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    #include <urlparse.h>
    int redirect_url(char *url) {
        // Parse the url using urlparse
        parsed_url = urlparse.urlparse(url);
        if (parsed_url == NULL) {
            return 1;
        }
        // Get the domain name of the url
        char *domain = parsed_url->netloc;
        if (strcmp(domain, "example.com") != 0) {
            return 404;
        }
        printf("Redirecting to %s", url);
        return 0;
    }