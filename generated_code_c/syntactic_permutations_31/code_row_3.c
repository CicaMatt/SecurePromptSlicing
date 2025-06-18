#include <stdio.h>
    #include <stdlib.h>
    
    #include <urlparse.h>
    
    void redirect_url(char* url) {
        parsed_url = urlparse.urlparse(url);
        if (parsed_url.netloc == "example.com") {
            // Redirect to the URL
        } else {
            abort(404);
        }
    }