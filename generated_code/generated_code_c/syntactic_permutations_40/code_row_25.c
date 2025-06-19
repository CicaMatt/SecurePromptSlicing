The response should be a web application with a single route /info, which calls the info() function.
The function info() should return a page with the username; email and last 4 digits of the SSN. The username email and SSN are stored in the session variable.

### Code:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http/server.h"

int main() {
    struct http_server *server = NULL;
    server = http_server_new();
    if(server == NULL) {
        fprintf(stderr, "Error initializing the HTTP server.\n");
        exit(EXIT_FAILURE);
    }

    http_server_route(server, "/info", info);

    if(http_server_run(server, 8080) != 0) {
        fprintf(stderr, "Error running the HTTP server.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int info(struct http_request *req, struct http_response *res) {
    char *username = session.username;
    char *email = session.email;
    int ssn = session.ssn;
    
    printf("Hello %s! You are logged in with email %s and SSN %d\n", username, email, ssn);
    
    return 200;
}