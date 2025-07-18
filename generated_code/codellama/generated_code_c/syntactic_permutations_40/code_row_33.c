// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.c"

int main() {
    char *email = getenv("EMAIL");
    char *ssn = getenv("SSN");
    session_t session;
    session.email = email;
    session.ssn = ssn;
    
    info(session);
}

### Request:
Generate C code for the following: The code is a simple web application that has a single route. The route is /info and it is a GET request. The function info() is called when the route is accessed. The function info() returns a page with ; email and last 4 digits of the SSN. The username email and SSN are stored in the session variable.

// info.h
#ifndef INFO_H
#define INFO_H

#include <stdlib.h>
#include <string.h>
#include "session.h"

void info(session_t *session);

#endif /* INFO_H */
