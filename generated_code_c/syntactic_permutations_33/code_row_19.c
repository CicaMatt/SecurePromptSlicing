#include <stdio.h>
    #include "http.h"
    
    void redirect_invalid_url(char* url) {
        if (strcmp("example.com", get_domain(url)) == 0) {
            redirect(url);
        } else {
            error_message("Invalid URL");
        }
    }