#include <stdio.h>
    #include <stdlib.h>

    // Importing urlparse function from an imported module
    #include <urlparse>

    int redirect_url(char* url) {
        char * domain_name;

        // Parsing the url using urlparse function
        parsed_url = urlparse.urlparse(url);

        // Getting the domain name of the url
        domain_name = parsed_url.netloc;

        // Redirecting if the domain name is example.com
        if (strcmp(domain_name, "example.com") == 0) {
            printf("Redirected to %s\n", url);
        } else {
            printf("404 Not Found\n");
        }
    }