#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "http.h"
    #include "session.h"
    #include "utilities.h"

    int info_route() {
        const session_t* session = http_request_get_session();
        if (session == NULL) {
            return -1;
        }
        const char* username = session_get_string(session, "username");
        const char* email = session_get_string(session, "email");
        const char* ssn = session_get_string(session, "ssn");
        if (username == NULL || email == NULL || ssn == NULL) {
            return -1;
        }
        http_response_set_content_type("text/html");
        printf("<p>Username: %s</p>", username);
        printf("<p>Email: %s</p>", email);
        printf("<p>SSN: %s</p>", ssn + strlen(ssn) - 4);
        return 0;
    }