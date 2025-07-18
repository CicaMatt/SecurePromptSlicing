#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http/http-server.h"
#include "session/session.h"

int info()
{
    session_start();
    char *email = (char *)session_get("email");
    char *username = (char *)session_get("username");
    char *ssn = (char *)session_get("ssn");
    char *html = "<p>Hello %s!</p>";
    int length = strlen(email) + strlen(username) + strlen(ssn) + strlen(html) + 1;
    char *message = (char *)malloc(sizeof(char) * length);
    sprintf(message, html, username);
    http_response_ok();
    http_header("Content-Type", "text/html");
    http_body(message);
}

int main()
{
    http_route("/info", info);
    http_server_start(8080, 4);
    return 1;
}
