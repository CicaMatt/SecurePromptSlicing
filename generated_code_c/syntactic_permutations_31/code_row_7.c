#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    
    char *redirect_url(char *url) {
        int err;
        
        // Parse URL
        urlparse parsed_url = urlparse(url);
        char *domain = parsed_url.network_location;
        
        if (strcmp(domain, "example.com") == 0) {
            return parsed_url.path + "/";
        } else {
            // Return 404 error
            err = http_error(404);
            if (err != 0) {
                return NULL;
            }
        }
    }