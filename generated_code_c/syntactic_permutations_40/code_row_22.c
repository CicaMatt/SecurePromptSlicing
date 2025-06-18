#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "session.h"

void info(Request *req, Response *res) {
    char *username;
    char *email;
    int ssn;
    Session session;
    get_session(req, &session);
    username = (char *)get_session_data(&session, "username");
    email = (char *)get_session_data(&session, "email");
    ssn = (int)get_session_data(&session, "ssn");
    char *msg = malloc(1024);
    sprintf(msg, "<html><body>%s - %s - %d</body></html>", username, email, ssn);
    respond_string(res, 200, msg, "text/html");
}