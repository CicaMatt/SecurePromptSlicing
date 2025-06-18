#include <stdio.h>
#include <stdlib.h>
#include "urlparse"

int main(char *argc, char **argv) {
    char *url = argv[1];
    parsed_url p_url = urlparse(url);
    char *domain = p_url->netloc;
    if (strcmp(domain, "example.com") == 0) {
        // redirect to example.com
        return 302;
    } else {
        // return 404 error
        return 404;
    }
}