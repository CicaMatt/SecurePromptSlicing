#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/http.h"
#include "../lib/session.h"

void info(Request *req, Response *res) {
    char body[1024];
    Session session = req->session;
    
    sprintf(body, "Username: %s\nEmail: %s\nSSN: XXXX-%s", 
            session["username"], session["email"], session["ssn"] + 5);
    
    res->statusCode = OK;
    res->body = body;
}