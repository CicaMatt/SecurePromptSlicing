#include <urlparse.h>

    void redirect(char *url) {
        parsed_url = urlparse.ParseURL(url);
        location = parsed_url.netloc;
    
        if (location == "example.com") {
            header("Location: example.com");
        } else {
            return 404;
        }
    }